#include "WorkCommand.h"
#include <iostream>
#include <algorithm>
WorkCommand::WorkCommand( boost::asio::io_service *ioservice) : socket(*ioservice), buffer(boost::asio::buffer(this->bufferData))
{
  this->command = "";
  this->bufferData.fill(' ');
  this->buffer = boost::asio::buffer(this->bufferData);
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

size_t WorkCommand::getBufferSize()
{
  return 10;
}

void WorkCommand::debug()
{
  std::cout << this->command << std::endl;
}

void WorkCommand::processBuffer( size_t bytes )
{
  this->command += std::string( std::begin(this->bufferData), std::begin(this->bufferData) + bytes );
  this->bufferData.fill(' ');
  this->buffer = boost::asio::buffer(this->bufferData);
}
