#pragma once
#include "common.h"
void task(std::promise<int>&);

void produce(std::promise<int>&);
void consume(std::future<int>&);

void take();
void give(std::promise<double>&);

namespace promise_exception {
	void produce(std::promise<int>&);
	void consume(std::future<int>&);
}

namespace promise_exception_ptr {
	void produce(std::promise<int>&);
	void consume(std::future<int>&);
}