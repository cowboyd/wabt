/*
 * Copyright 2017 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WABT_BINARY_ERROR_HANDLER_H_
#define WABT_BINARY_ERROR_HANDLER_H_

#include <stdint.h>
#include <stdio.h>

#include <string>

namespace wabt {

class BinaryErrorHandler {
 public:
  virtual ~BinaryErrorHandler() {}

  // Returns true if the error was handled.
  virtual bool OnError(uint32_t offset, const std::string& error) = 0;
};

class BinaryErrorHandlerFile : public BinaryErrorHandler {
 public:
  enum class PrintHeader {
    Never,
    Once,
    Always,
  };

  BinaryErrorHandlerFile(FILE* file = stderr,
                         const std::string& header = std::string(),
                         PrintHeader print_header = PrintHeader::Never);

  bool OnError(uint32_t offset, const std::string& error) override;

 private:
  void PrintErrorHeader();

  FILE* file_;
  std::string header_;
  PrintHeader print_header_;
};

}  // namespace wabt

#endif // WABT_BINARY_ERROR_HANDLER_H_
