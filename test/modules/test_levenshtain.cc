#include <catch.hpp>
#include <string>

#include "../../src/modules/levenshtein.cc"

TEST_CASE("Levenshtein returns a correct result after comparison", "[levenshtein]") {
    Sequence t1, t2;
    LevenshteinDistance compare;
    compare.setIdentity(0.05f);

    SECTION("Compare two equal strings") {
        t1.setSequence("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
        t2.setSequence("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");

        REQUIRE(compare.compare(&t1, &t2) == true);
    }

    SECTION("Compare two very different strings") {
        t1.setSequence("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
        t2.setSequence("ggatcctcatagcggctattgcgaaaagctatttcgcggccctagcga");

        REQUIRE(compare.compare(&t1, &t2) == false);
    }
}