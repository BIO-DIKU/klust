#ifndef SRC_MAIN_CONTROL_H
#define SRC_MAIN_CONTROL_H

#include <string>

#include "FastaReader.h"
#include "FastaWriter.h"
#include "InterfaceCompare.h"
#include "InterfaceClust.h"
#include "InterfaceKmergen.h"

class MainControl {
    private:
        MainControl(const MainControl&) = delete;
        MainControl& operator=(const MainControl&) = delete;

        MainControl();

    public:
        virtual ~MainControl();

        static MainControl* instance();
        int run();

        void setIdentity(float id);
        float getIdentity() const;

        void setInputFile(const std::string& filename);
        void setOutputFile(const std::string& filename);

        void setKmergen(InterfaceKmergen* kmergen);
        void setCompare(InterfaceCompare* compare);
        void setClust(InterfaceClust* clust);

    private:
        FastaReader* m_reader;
        FastaWriter* m_writer;

        float m_identity; // Similarity identity

        InterfaceKmergen* m_kmergen;
        InterfaceCompare* m_compare;
        InterfaceClust* m_clust;
};

#endif // SRC_MAIN_CONTROL_H
