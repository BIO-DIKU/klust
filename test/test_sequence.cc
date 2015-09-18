#include <catch.hpp>

#include "../src/sequence.cc"

TEST_CASE("sequence can be constructed, copied and moved", "[sequence]") {

    Sequence t1;
    Sequence t2 = Sequence("Test 1", "Comment 1", 42);

    REQUIRE(t1.m_sequence == "");
    REQUIRE(t1.m_comment == "");
    REQUIRE(t1.m_lineNumber == -1);
    REQUIRE(t1.m_kmers == nullptr);
    REQUIRE(t1.m_kmersSize == 0);

    REQUIRE(t2.m_sequence == "Test 1");
    REQUIRE(t2.m_comment == "Comment 1");
    REQUIRE(t2.m_lineNumber == 42);
    
    REQUIRE(t2.kmersGenerated() == false);

    SECTION("Copy Sequence 2 to Sequence 1") {
        t1 = t2;

        REQUIRE(t1.m_sequence == "Test 1");
        REQUIRE(t1.m_comment == "Comment 1");
        REQUIRE(t1.m_lineNumber == 42);
    }
    SECTION("Use copy contructor for new Sequence") {
        Sequence t3(t2);

        REQUIRE(t3.m_sequence == "Test 1");
        REQUIRE(t3.m_comment == "Comment 1");
        REQUIRE(t3.m_lineNumber == 42);
    }
    SECTION("Use move contructor for new Sequence") {
        Sequence t4 = std::move(t2);

        REQUIRE(t4.m_sequence == "Test 1");
        REQUIRE(t4.m_comment == "Comment 1");
        REQUIRE(t4.m_lineNumber == 42);

        REQUIRE(t2.m_sequence == "");
        REQUIRE(t2.m_comment == "");
        REQUIRE(t2.m_lineNumber == 42);
    }
}