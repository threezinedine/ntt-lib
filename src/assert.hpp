#pragma once
#include "common.hpp"
#include <assert.h>

/**
 * Used as the implementation of the method, function, or feature is not yet implemented
 *      so that the program still can be compiled and run without any error but will
 *      raise the error when the method, function, or feature is called.
 */
#define NTT_ASSERT_NOT_IMPLEMENTED assert(false && "Not implemented yet")

/**
 * Used as the implementation of the method, function, or feature is not yet implemented
 *      so that the program still can be compiled and run without any error but will
 *      raise the error when the method, function, or feature is called.
 *
 * Differ from NTT_ASSERT_NOT_IMPLEMENTED, this macro will show the message when the
 *      assertion is raised.
 *
 * @param msg The message that will be shown when the assertion is raised.
 */
#define NTT_ASSERT_NOT_IMPLEMENTED_M(msg) assert(false && msg)