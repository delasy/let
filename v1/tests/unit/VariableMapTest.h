/**
 * @created_at: 2019-06-24 00:56:57
 * @author: Aaron Delasy
 * @license_start
 *
 * Copyright (c) 2018-2019  Aaron Delasy
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @license_end
 */

#ifndef TESTS_VARIABLEMAPTEST_H
#define TESTS_VARIABLEMAPTEST_H

#include "../../src/VariableMap.h"

namespace let {
  class VariableMapTest : public testing::Test {
   protected:
    VariableMap variableMap0_;
    VariableMap variableMap1_;
    VariableMap variableMap2_;

    void SetUp() override {
      this->variableMap1_.set("a", 1);

      this->variableMap2_.set("a", 1);
      this->variableMap2_.set("b", 2);
    }
  };

  TEST_F(VariableMapTest, DefaultConstructor) {
    EXPECT_TRUE(this->variableMap0_.isEmpty());
  }

  TEST_F(VariableMapTest, Get) {
    VariableMapItem itemA0 = this->variableMap0_.get("a");

    EXPECT_TRUE(itemA0.isEmpty());

    VariableMapItem itemA1 = this->variableMap1_.get("a");

    EXPECT_EQ(itemA1.size, 1);

    VariableMapItem itemB1 = this->variableMap1_.get("b");

    EXPECT_TRUE(itemB1.isEmpty());

    VariableMapItem itemA2 = this->variableMap2_.get("a");

    EXPECT_EQ(itemA2.size, 1);

    VariableMapItem itemB2 = this->variableMap2_.get("b");

    EXPECT_EQ(itemB2.size, 2);

    VariableMapItem itemC2 = this->variableMap2_.get("c");

    EXPECT_TRUE(itemC2.isEmpty());
  }

  TEST_F(VariableMapTest, Set) {
    EXPECT_TRUE(this->variableMap0_.isEmpty());

    VariableMapItem itemA0 = this->variableMap0_.set("a", 1);

    EXPECT_EQ(this->variableMap0_.getSize(), 1);
    EXPECT_EQ(itemA0.address, 0x2000);
    EXPECT_EQ(itemA0.addressLocal, 0);
    EXPECT_EQ(itemA0.name, "a");
    EXPECT_EQ(itemA0.size, 1);

    EXPECT_EQ(this->variableMap1_.getSize(), 1);

    VariableMapItem itemB1 = this->variableMap1_.set("b", 2);

    EXPECT_EQ(this->variableMap1_.getSize(), 2);
    EXPECT_EQ(itemB1.address, 0x2001);
    EXPECT_EQ(itemB1.addressLocal, 1);
    EXPECT_EQ(itemB1.name, "b");
    EXPECT_EQ(itemB1.size, 2);

    EXPECT_EQ(this->variableMap2_.getSize(), 2);

    VariableMapItem itemC2 = this->variableMap2_.set("c", 3);

    EXPECT_EQ(this->variableMap2_.getSize(), 3);
    EXPECT_EQ(itemC2.address, 0x2003);
    EXPECT_EQ(itemC2.addressLocal, 3);
    EXPECT_EQ(itemC2.name, "c");
    EXPECT_EQ(itemC2.size, 3);
  }
}

#endif
