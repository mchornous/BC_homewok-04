#include <iostream>
#include "myString.h"
#include <string>
#include <gtest/gtest.h>

//test for functions append,length,buffer and myString(const char*) constructor
TEST(String_append_lenght_and_constructor_test,two_strings){
   myString s2("chornous");
   myString s1("mykola");

   ASSERT_STREQ("chornous",s2.getBuffer());
   ASSERT_STREQ("mykola", s1.getBuffer());

   s1.append(s2, s2.length());
   EXPECT_EQ(14,s1.length());
   ASSERT_STREQ("mykolachornous",s1.getBuffer());
}
//test for insert string function
TEST(String_insert_test,two_strings){
  myString s1("Hello");
  myString s2("World");
  s1.insert(0,s2,5);
  ASSERT_STREQ("WorldHello", s1.getBuffer());
}

//test for insert char function
TEST(String_insert_char_test,char_string){
 myString s1("Hello");
 s1.insert(0,"W",1);
 ASSERT_STREQ("WHello",s1.getBuffer());
}
//test for swap function
TEST(String_swap_test,two_strings){
  myString s1("Hello");
  myString s2("World");
 s1.swap(s2);
}
//test for resize function
TEST(String_resize_test,string_and_size){
  myString s1("Hello World");
  s1.resize(5);
  EXPECT_EQ(4,s1.length());
  ASSERT_STREQ("Hell",s1.getBuffer());
}

//test for substr
TEST(String_substr_test,string){
  myString s1("Hello World");
  myString s2("World");
  int result = s1.substr(s2);
  EXPECT_EQ(6,result);
}

//test for clear and compare functions
TEST(String_compare_clear,STRING){
  myString s1("Hello World");
  myString s2("World");
  if(s1.compare(s2)){
    s2.clear();
  }
  EXPECT_EQ(0,s2.length());
}


int main(int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);
	  return RUN_ALL_TESTS();
}
