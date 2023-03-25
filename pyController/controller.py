import sys
import requests
import json
import random
import time
import subprocess
from requests_futures.sessions import FuturesSession
from dataclasses import dataclass

def sendRecvJson(url: str, payloadObj: "any|None", bearerKey: str|None = None, returnsMessage=False):
    headers = {}
    if payloadObj is not None:
        headers["Content-Type"] = "application/json"
    if bearerKey is not None:
        headers["Authorization"] = f"Bearer {bearerKey}"

    print(f"===================================Sending to {url} :")
    if payloadObj is not None:
        print("=   "+json.dumps(payloadObj))
    print(f"===================================")

    if payloadObj is None:
        response = requests.get(url, headers=headers)
    else:
        response = requests.post(url, headers=headers, json=payloadObj)

    if response.status_code >= 200 and response.status_code <= 299:
        # Response successfully received
        responseObj = json.loads(response.text)
        if not returnsMessage and "message" in responseObj:
            raise RuntimeError(f"Request failed with message: {responseObj['message']}")
        return responseObj
    else:
        # Error handling for failed request
        raise RuntimeError(f"Request failed with status code: {response.status_code}")

def sendAsyncJson(session: FuturesSession, url: str, payloadObj: "any|None", bearerKey: str|None = None):
    headers = {}
    if payloadObj is not None:
        headers["Content-Type"] = "application/json"
    if bearerKey is not None:
        headers["Authorization"] = f"Bearer {bearerKey}"

    print(f"===================================Sending to {url} :")
    if payloadObj is not None:
        print("=   "+json.dumps(payloadObj))
    print(f"===================================")


    if payloadObj is None:
        return session.get(url, headers=headers, json=payloadObj)
    else:
        return session.post(url, headers=headers, json=payloadObj)

def recvAsyncJson(future, returnsMessage=False):
    responseObj = json.loads(future.result().text)
    if not returnsMessage and "message" in responseObj:
        raise RuntimeError(f"Request failed with message: {responseObj['message']}")

    return responseObj

class Figure:
    def __init__(self, jsonState: any) -> None:
        self.vrsta = jsonState["oznaka"]
        pass

FigCountPerColor = 48

class Board:
    def __init__(self, jsonState: any, whiteFigs, blackFigs) -> None:
        self.whiteFigs: list[int] = whiteFigs
        self.blackFigs: list[int] = blackFigs

        self.fields = [
            [
                self.getNewFigInd(fig)
                for fig in line
            ]
            for line in jsonState["board"]
        ]

        self.whiteCaptured = [
            self.getNewFigInd(fig)
            for fig in jsonState["whitePiecesPlacement"]
        ] + [
            self.getNewFigInd(fig)
            for fig in jsonState["whitePijanPlacement"]
        ]

        self.blackCaptured = [
            self.getNewFigInd(fig)
            for fig in jsonState["blackPiecesPlacement"]
        ] + [
            self.getNewFigInd(fig)
            for fig in jsonState["blackPijanPlacement"]
        ]
        
    def getNewFigInd(self, jsonState: "any|None") -> int:
        if jsonState is None:
            return -1
        else:
            if jsonState["black"] == True:
                self.blackFigs.append(Figure(jsonState))
                return len(self.blackFigs)-1 + FigCountPerColor
            else:
                self.blackFigs.append(Figure(jsonState))
                return len(self.blackFigs)-1 + FigCountPerColor


class GameState:
    def __init__(self, jsonState: any, whiteOnBoard1: bool) -> None:
        myPlyInd = 0 if whiteOnBoard1 else 1
        enemyPlyInd = 1 if whiteOnBoard1 else 0
        self.whiteFigs: list[Figure] = []
        self.blackFigs: list[Figure] = []
        self.board1 = Board(jsonState["boardState1"], self.whiteFigs, self.blackFigs)
        self.board2 = Board(jsonState["boardState2"], self.whiteFigs, self.blackFigs)
        self.turn = myPlyInd if jsonState["boardState1"]["whiteMoves"] == whiteOnBoard1 or jsonState["boardState2"]["whiteMoves"] != whiteOnBoard1 else enemyPlyInd
        self.boardTurn = 0 if (jsonState["boardState1"]["whiteMoves"] and whiteOnBoard1) or (not jsonState["boardState2"]["whiteMoves"] and not whiteOnBoard1) else 1
        self.phase = jsonState["boardState1"]["phase"]
        self.numInvalid = jsonState["illegalMoveCounter"]
        pass

    def __str__(self) -> str:
        boardIndsStr = "".join([ind for board in [self.board1, self.board2] for line in board for ind in line])
        figureLettersStr = ""
        for fig in self.whiteFigs:
            figureLettersStr.append(fig.vrsta)
        for i in range(len(self.whiteFigs), 48):
            figureLettersStr.append("-")
        for fig in self.blackFigs:
            figureLettersStr.append(fig.vrsta)
        for i in range(len(self.blackFigs), 48):
            figureLettersStr.append("-")
        return f"{self.turn} {self.boardTurn} {boardIndsStr} {figureLettersStr}"



def main():
    # globals
    gameState: GameState = None
    asyncSession = FuturesSession()

    # read params
    adminToken: str|None = None
    url = "http://localhost:8080"
    gameId: int|None = None
    playerInds = [0, 1]
    playerNames = ["player1", "player2"]
    playerPasswords = ["sifra1", "sifra2"]
    playerControllers: list[str] = ["bot", "bot"]
    playerTokens: list[str|None] = [None, None]

    i = 1
    while i < len(sys.argv):
        comm = sys.argv[i]
        i += 1
        par = sys.argv[i]
        if comm == "id":
            gameId = par
        elif comm == "control":#manual|bot|remote
            playerControllers = par.split(",")
        elif comm == "url":
            url = par
        elif comm == "token1":
            playerTokens[0] = par
        elif comm == "token2":
            playerTokens[1] = par
        else:
            raise RuntimeError(f"Unknown command {comm}")
        i += 1

    # Create the game
    if adminToken is None:
        print("Logging in as admin..."); t=time.time()
        resp = sendRecvJson(url+"/user/login", {"username": "admin", "password": "admin"})
        adminToken = resp["token"]
        print(f"Token: {adminToken}")
        print(f"Logged in as admin! ({time.time()-t}s)")
    
    # Logins
    playerJoiningHttpRequests = [None, None]
    playerJoiningTimers = [None, None]
    for i in playerInds:
        if playerControllers[i] != "remote":
            if playerTokens[i] is None:
                print(f"Logging in as {playerNames[i]}..."); t=time.time()
                resp = sendRecvJson(url+"/user/login", {"username": playerNames[i], "password": playerPasswords[i]})
                playerTokens[i] = resp["token"]
                print(f"Logged in as {playerNames[i]}! ({time.time()-t}s)")

    # Game create
    if gameId is None:
        gameId = random.randint(0, 1000000)
        print(f"Creating game {gameId} as admin..."); t=time.time()
        resp = sendRecvJson(url+"/game/createGame", {"gameId": gameId, "playerUsernames": playerNames}, adminToken, returnsMessage=True)
        print(f"Creating game {gameId} as admin! ({time.time()-t}s)")
        print("Stvaranje igre:", resp["message"])
    
    # Game joins
    playerJoiningHttpRequests = [(None), None]
    playerJoiningTimers = [None, None]
    for i in playerInds:
        if playerControllers[i] != "remote":
            print(f"Joining game as {playerNames[i]}..."); playerJoiningTimers[i]=time.time()
            playerJoiningHttpRequests[i] = sendAsyncJson(asyncSession, url+"/game/joinGame", None, playerTokens[i])

    for i in playerInds:
        if playerControllers[i] != "remote":
            print(f"Waiting for response for {playerNames[i]}...");
            resp = recvAsyncJson(playerJoiningHttpRequests[i])
            print(f"Joined game as {playerNames[i]}! ({time.time()-playerJoiningTimers[i]}s)")
            gameState = GameState(json.loads(resp["gameState"]))

    # start the simulator!
    simulatorProc = subprocess.Popen(['watch', 'ls'], stdout=subprocess.PIPE, stdin=subprocess.PIPE)

    # game loop
    print("Starting the game loop!")
    print("-------------------------------------------")
    running = True
    while running:
        print(f"Player {gameState.turn}'s turn!")
        moveServerStr = ""

        if playerControllers[gameState.turn] == "manual":
            if gameState.phase == 0:
                print(f"Enter move (M-oldX-oldY-newX-newY or P-FigType-newX-newY)")
                moveServerStr = input()
            elif gameState.phase == 1:
                print(f"Enter move (P-FigType-newX-newY)")
                moveServerStr = input()
        elif playerControllers[gameState.turn] == "bot":
            simulatorProc.stdin.write(f"set {str(gameState)}".encode("utf-8"))
            moveServerStr = simulatorProc.stdout.readline().decode("utf-8")
            timeStr = simulatorProc.stdout.readline().decode("utf-8")
            print(f"Calced move {moveServerStr} in {timeStr}")


        if playerControllers[i] != "remote":
            oldInvalids = gameState.numInvalid
            resp = sendRecvJson(url+"/game/doAction", {"action": moveServerStr}, playerTokens[gameState.turn])
            gameState = GameState(json.loads(resp["gameState"]))
            if gameState.numInvalid > oldInvalids:
                print("ERROR: Invalid move")

    # cleanup
    simulatorProc.terminate()


if __name__ == "__main__":
    try:
        main()
    except RuntimeError as e:
        print("ERROR =:÷×÷×÷×÷×÷;<><>><~~~~~~~      :'(\n")
        print(e.args[0])