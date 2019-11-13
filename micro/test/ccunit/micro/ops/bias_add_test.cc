// Copyright 2018 The MACE Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "gtest/gtest.h"
#include "micro/ops/bias_add.h"
#include "micro/ops/gtest_utils.h"
#include "micro/ops/substitute_op.h"
#include "micro/ops/test_utils.h"

namespace micro {
namespace ops {
namespace test {

class BiasAddOpTest : public ::testing::Test {};

namespace {

void BiasAddSimple() {
  float input[12] = {5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15};
  int32_t input_dims[4] = {1, 6, 2, 1};
  float bias[1] = {0.5f};
  int32_t bias_dims[1] = {1};

  float output[12] = {0};
  int32_t output_dims[4] = {0};
  float expect[12] =
      {5.5, 5.5, 7.5, 7.5, 9.5, 9.5, 11.5, 11.5, 13.5, 13.5, 15.5, 15.5};
  int32_t expect_dims[4] = {1, 6, 2, 1};

  BiasAddOp bias_add_op;
  framework::SubstituteOp substitude_op;
  substitude_op.AddInput(input, input_dims, 4)
      .AddInput(bias, bias_dims, 1)
      .AddOutput(output, output_dims, 4);

  bias_add_op.Init(NULL, reinterpret_cast<framework::OpContext *>(
      &substitude_op), NULL);
  bias_add_op.Run();

  ExpectTensorNear<float>(output, output_dims, 4, expect, expect_dims, 4, 1e-4);
}

}  // namespace

TEST_F(BiasAddOpTest, BiasAddSimple) {
  BiasAddSimple();
}

}  // namespace test
}  // namespace ops
}  // namespace micro
