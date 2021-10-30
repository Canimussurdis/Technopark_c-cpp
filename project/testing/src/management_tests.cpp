#include <gtest/gtest.h>
#include <random>
#include <memory>
#include "utils.h"

extern "C" {
#include "operations.h"
#include "data_management.h"
}

const size_t LIST_LENGTH = 51;
const size_t MIN_LENGHT = 1;
const size_t MAX_LENGHT = 1000;
const double DOUBLE_1 = 5.000123;
const double DOUBLE_2 = 5.00123;
const double DOUBLE_SMALL_1 = 0.0000001111;
const double DOUBLE_SMALL_2 = 0.0000003123;
const double DOUBLE_BIG_1 = 100000000.00012;
const double DOUBLE_BIG_2 = 100000000.000123;

TEST(MANAGEMENT_TEST, CREATE_NODE) {
  errno = 0;
  auto *node = create_node();
  free(node);
  ASSERT_TRUE(!node == (errno == ENOMEM));
}

TEST(MANAGEMENT_TEST, FREE_NODE) {
  auto *nodeFirst = create_node();
  auto *nodeSecond = create_node();
  if (!nodeFirst || !nodeSecond) {
    throw std::runtime_error("no memory");
  }
  free_node(nullptr);
  free_node(nodeFirst);
nodeSecond->data.aircraft_name = static_cast<char *>(malloc(1));
  if (!nodeSecond->data.aircraft_name) {
    throw std::runtime_error("no memory");
  }
  free_node(nodeSecond);
  SUCCEED();
}

TEST(MANAGEMENT_TEST, FREE_LIST) {
  auto *nodeFirst = create_node();
  auto *nodeSecond = create_node();
  if (!nodeFirst || !nodeSecond) {
    throw std::runtime_error("no memory");
  }
  nodeFirst->next = nodeSecond;
  free_list(nodeFirst);
  SUCCEED();
}

TEST(MANAGEMENT_TEST, INSERT_NODE_1) {
  aircraft_node *head = nullptr;
  auto node = std::make_shared<aircraft_node>();
  node->next = nullptr;

  ASSERT_EQ(insert_node(nullptr, node.get()), -1);
  ASSERT_EQ(insert_node(nullptr, nullptr), -1);
  ASSERT_EQ(insert_node(&head, node.get()), 0);
  ASSERT_EQ(head, node.get());
}

/*
TEST(MANAGEMENT_TEST, INSERT_NODE_2) {
  std::array<aircraft_node, LIST_LENGTH> nodes = {0, 0, 0, 0, 0, nullptr, nullptr};
  aircraft_node *head = nullptr;
  std::mt19937 gen(TestConfig::testSeed);
  std::uniform_int_distribution<size_t> distrName (MIN_LENGHT, MAX_LENGHT);
  std::uniform_int_distribution<size_t> distrModel (MIN_LENGHT, MAX_LENGHT);
  std::uniform_int_distribution<size_t> distrUsage (MIN_LENGHT, MAX_LENGHT);
  std::uniform_int_distribution<size_t> distrCrewSize (MIN_LENGHT, MAX_LENGHT);
  std::uniform_int_distribution<size_t> distrRange (MIN_LENGHT, MAX_LENGHT);
  
  for (auto &node :nodes) {
    node.data.name = distrName(gen);
    node.data.model = distrModel(gen);
    node.data.usage = distrUsage(gen);
    node.data.crew_size = distrCrewSize(gen);
    node.data.range_of_flight = distrRange(gen);
    
    ASSERT_EQ(insert_node(&head, &node), 0);
  }
  
  ASSERT_TRUE(head);
  
  aircraft_node *previous = head;
  aircraft_node *current = head->next;
  while (current) {
    ASSERT_TRUE(previous->data.range_of_flight <= current->data.range_of_flight);
    current = current->next;
  }
}
*/

TEST(MANAGEMENT_TEST, COMPARISON_EQUAL) {
  ASSERT_EQ(is_less(DOUBLE_BIG_1, DOUBLE_BIG_1), 0);
  ASSERT_EQ(is_less(DOUBLE_SMALL_1, DOUBLE_SMALL_1), 0);
  ASSERT_EQ(is_less(DOUBLE_1, DOUBLE_1), 0);
}

/*
TEST(MANAGEMENT_TEST, COMPARISON_LESS) {
  ASSERT_EQ(is_less(DOUBLE_BIG_1, DOUBLE_BIG_2), 0);
  ASSERT_EQ(is_less(DOUBLE_SMALL_1, DOUBLE_SMALL_2), 1);
  ASSERT_EQ(is_less(DOUBLE_1, DOUBLE_2), 1);
}
*/

TEST(MANAGEMENT_TEST, COMPARISON_GREATER) {
  ASSERT_EQ(is_less(DOUBLE_BIG_2, DOUBLE_BIG_1), 0);
  ASSERT_EQ(is_less(DOUBLE_SMALL_2, DOUBLE_SMALL_2), 0);
  ASSERT_EQ(is_less(DOUBLE_2, DOUBLE_1), 0);
}
