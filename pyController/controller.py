import sys
import requests
import json
import random
import time
import aiohttp
import asyncio
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

async def sendAsyncJson(session, url: str, payloadObj: "any|None", bearerKey: str|None = None):
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
        async with session.get(url, headers=headers, json=payloadObj) as response:
            return await response.json()
    else:
        async with session.post(url, headers=headers, json=payloadObj) as response:
            return await response.json()

async def recvAsyncJson(promise, returnsMessage=False):
    responseObj = await promise
    if not returnsMessage and "message" in responseObj:
        raise RuntimeError(f"Request failed with message: {responseObj['message']}")

    return responseObj



class GameState:
    def __init__(self, jsonState: any) -> None:
        pass



async def main():
    # globals
    gameState: GameState = None

    # read params
    adminToken: str|None = None
    url = "http://localhost:8080"
    gameId: int|None = None
    playerInds = [0, 1]
    playerNames = ["player1", "player2"]
    playerPasswords = ["sifra1", "sifra2"]
    playerControllers: list[str] = ["manual", "manual"]
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
        
    async with aiohttp.ClientSession() as asyncSession:

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
                resp = await recvAsyncJson(playerJoiningHttpRequests[i])
                print(f"Joined game as {playerNames[i]}! ({time.time()-playerJoiningTimers[i]}s)")
                gameState = GameState(resp["gameState"])

        # game loop
        running = True
        while running:
            pass


if __name__ == "__main__":
    try:
        loop = asyncio.get_event_loop()
        loop.run_until_complete(main())
    except RuntimeError as e:
        print("ERROR =:÷×÷×÷×÷×÷;<><>><~~~~~~~        :'(\n")
        print(e.args[0])