
#include <gtest/gtest.h>
#include <experimental/filesystem>
#include <fstream>
#include "utils.h"

extern "C" {
#include "operations.h"
}
const std::string ERROR_AIRCRAFT_NAME = "0 0 0 0 0 error_aircraft_name\n";
namespace fs = std::experimental::filesystem;

TEST_F(IO_TEST, RRINT_ERROR_AIRCRAFT) {
    auto node = std::make_shared<aircraft_node>();
    node->data.name = 0;
    node->data.model = 0;
    node->data.usage = 0;
    node->data.crew_size = 0;
    node->data.range_of_flight = 0;
    node->next = nullptr;
    node->data.aircraft_name = nullptr;
    print_list(node.get());
    ASSERT_EQ(getTestOutput(), ERROR_AIRCRAFT_NAME);
}

TEST_F(IO_TEST, COMPLEX_TEST) {
    aircraft_node *head = nullptr;
    for (auto &entity : fs::directory_iterator(TestConfig::testDataPath)) {
        setTestInput(entity / "in.txt");
        errno = 0;
        head = get_ordered_list();
        ASSERT_TRUE(!head == (errno == ENOMEM));
        print_list(head);
        free_list(head);
        ASSERT_EQ(getTestOutput(), file2string(entity / "out.txt"));
        
      
        clearTestOutput();
    }
}

