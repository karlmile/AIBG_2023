cmake_minimum_required(VERSION 3.0)

######################################
# User build configuration
######################################


# =========================
# File copying target
# =========================

add_custom_command(
	OUTPUT
		${CMAKE_CURRENT_BINARY_DIR}/controller.py
	COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generators/generator.py
		--inregexmacro ${CMAKE_CURRENT_SOURCE_DIR}/autosyntaxdef/unicodeREMacrosAutogen.txt
		--inlexer ${CMAKE_CURRENT_SOURCE_DIR}/syntaxdef/lexer.txt
		--insemanticnodes ${CMAKE_CURRENT_SOURCE_DIR}/syntaxdef/semanticNodes.txt
		--inparser ${CMAKE_CURRENT_SOURCE_DIR}/syntaxdef/parser.txt
		--inlexerh ${CMAKE_CURRENT_SOURCE_DIR}/autoinclude/chakralLexerAutogen.h
		--outparserh ${CMAKE_CURRENT_SOURCE_DIR}/autoinclude/chakralParserAutogen.h
		--outparsercpp ${CMAKE_CURRENT_SOURCE_DIR}/autosrc/chakralParserAutogen.cpp
		--extraparserheaders ${CMAKE_CURRENT_SOURCE_DIR}/include/chakralParserPrereq${ParserTypeSuffix}.h ${CMAKE_CURRENT_SOURCE_DIR}/autoinclude/chakralSemanticNodesAutogen.h
		--outsemanticnodesh ${CMAKE_CURRENT_SOURCE_DIR}/autoinclude/chakralSemanticNodesAutogen.h
		--outsemanticnodescpp ${CMAKE_CURRENT_SOURCE_DIR}/autosrc/chakralSemanticNodesHybridgen.cpp
		--extrasemanticinclheaders ${CMAKE_CURRENT_SOURCE_DIR}/include/chakralParserPrereq${ParserTypeSuffix}.h ${CMAKE_CURRENT_SOURCE_DIR}/include/chakralSemanticsPrereq.h
		--extrasemanticimplheaders ${CMAKE_CURRENT_SOURCE_DIR}/include/chakralServer.h
		--parsertype ${ParserType}
	DEPENDS
		${CMAKE_CURRENT_SOURCE_DIR}/controller.py
	COMMENT "Generating parser files"
)

add_custom_target(
	generate ALL
	DEPENDS
		${CMAKE_CURRENT_BINARY_DIR}/controller.py
)

add_custom_target(controller)