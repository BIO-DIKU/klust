#include <catch.hpp>

#include "../src/sequence.cc"

TEST_CASE("sequences can be constructed, copied and moved", "[sequence]") {
  SeqEntry t1;
  SeqEntry t2 = SeqEntry("Name", "Sequence", "Scores", SeqEntry::SeqType::dna);

  REQUIRE(t1.seq_name() == "");
  REQUIRE(t1.seq() == "");
  REQUIRE(t1.scores() == "");
  REQUIRE(t1.type() == SeqEntry::SeqType::unknown);

  REQUIRE(t2.seq_name() == "Name");
  REQUIRE(t2.seq() == "Sequence");
  REQUIRE(t2.scores() == "Scores");
  REQUIRE(t2.type() == SeqEntry::SeqType::dna);

  SECTION("Copy SeqEntry 2 to SeqEntry 1") {
    t1 = t2;

    REQUIRE(t1.seq_name() == "Name");
    REQUIRE(t1.seq() == "Sequence");
    REQUIRE(t1.scores() == "Scores");
    REQUIRE(t1.type() == SeqEntry::SeqType::dna);
  }

  SECTION("Use copy contructor for new SeqEntry") {
    SeqEntry t3(t2);

    REQUIRE(t3.seq_name() == "Name");
    REQUIRE(t3.seq() == "Sequence");
    REQUIRE(t3.scores() == "Scores");
    REQUIRE(t3.type() == SeqEntry::SeqType::dna);
  }

  SECTION("Use move contructor for new SeqEntry") {
    SeqEntry t4 = std::move(t2);

    REQUIRE(t4.seq_name() == "Name");
    REQUIRE(t4.seq() == "Sequence");
    REQUIRE(t4.scores() == "Scores");
    REQUIRE(t4.type() == SeqEntry::SeqType::dna);

    REQUIRE(t2.seq_name() == "");
    REQUIRE(t2.seq() == "");
    REQUIRE(t2.scores() == "");
    REQUIRE(t2.type() == SeqEntry::SeqType::dna);
  }
}

TEST_CASE("subsequences can be extracted from sequences", "[sequence]") {
  SeqEntry t1 = SeqEntry("Name", "Sequence", "Scores", SeqEntry::SeqType::rna);

  REQUIRE(t1.seq_name() == "Name");
  REQUIRE(t1.seq() == "Sequence");
  REQUIRE(t1.scores() == "Scores");
  REQUIRE(t1.type() == SeqEntry::SeqType::rna);

  SeqEntry t2 = t1.SubSeq(2, 4);

  // t1 stays unchanged
  REQUIRE(t1.seq_name() == "Name");
  REQUIRE(t1.seq() == "Sequence");
  REQUIRE(t1.scores() == "Scores");
  REQUIRE(t1.type() == SeqEntry::SeqType::rna);

  // t2 contains expected subsequence of t1 and they are otherwise identical
  REQUIRE(t2.seq_name() == "Name");
  REQUIRE(t2.seq() == "quen");
  REQUIRE(t2.scores() == "Scores");
  REQUIRE(t2.type() == SeqEntry::SeqType::rna);
}
