#!/bin/bash
g++ -g -o QueueProcessor main.cpp SocketHandler.cpp WorkerThread.cpp WorkQueue.cpp WorkCommand.cpp -lboost_system -lboost_thread -lboost_context -lboost_coroutine -ljsoncpp
