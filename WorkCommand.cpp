#include "WorkCommand.h"
#include <iostream>
#include <algorithm>
#include <json/json.h>

WorkCommand::WorkCommand( boost::asio::io_service *ioservice) : socket(*ioservice), buffer(boost::asio::buffer(this->bufferData))
{
  this->command = "";
  this->bufferData.fill(' ');
  this->buffer = boost::asio::buffer(this->bufferData);
  this->json_valid = false;
}

WorkCommand::~WorkCommand() {}

tcp::socket* WorkCommand::getSocket()
{
  return &this->socket;
}

boost::asio::mutable_buffers_1* WorkCommand::getBuffer()
{
  return &buffer;
}

void WorkCommand::processBuffer( size_t bytes )
{
  this->command += std::string( std::begin(this->bufferData), std::begin(this->bufferData) + bytes );
  this->validateJSON();
  
  this->bufferData.fill(' ');
  this->buffer = boost::asio::buffer(this->bufferData);
}

void WorkCommand::validateJSON()
{
  Json::Reader reader;
  Json::Value root;
  this->json_valid = reader.parse( this->command, root );
}

bool WorkCommand::isCommandValid()
{
  return this->json_valid;
}

std::string WorkCommand::getSystemCommand()
{
  Json::Reader reader;
  Json::Value root;
  reader.parse( this->command, root );
  std::string message = "/web/bin/console " + root["command"].asString() + " ";
  for( auto itr = root["parameters"].begin(); itr != root["parameters"].end(); itr++ )
    message += "--" + itr.key().asString() + "=" + (*itr).asString() + " ";
  
  return message;  
}