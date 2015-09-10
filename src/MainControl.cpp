#include "MainControl.h"

MainControl::MainControl() :
    m_reader(new FastaReader()),
    m_writer(new FastaWriter()),
    m_identity(0.9f)
{
    m_writer->openCoutWriter();
}

MainControl::~MainControl() {
    if(m_reader)
        delete m_reader;
    if(m_writer)
        delete m_writer;
}

MainControl* MainControl::instance() {
    static MainControl control;
    return &control;
}

int MainControl::run() {
    if(m_compare == nullptr || m_clust == nullptr || m_kmergen == nullptr) {
        return -1;
    }

    m_compare->setIdentity(m_identity);
    m_clust->setCompare(m_compare);
    m_clust->setKmergen(m_kmergen);

    Sequence seq;
    while(!m_reader->getNextLine(seq)) {
        if(m_clust->addSequence(seq) > 0) {
            m_writer->write(seq);
        }
    }

    return 0;
}

void MainControl::setIdentity(float id) {
    m_identity = id;
}

float MainControl::getIdentity() const {
    return m_identity;
}

void MainControl::setInputFile(const std::string& filename) {
    m_reader->openReader(filename);
}

void MainControl::setOutputFile(const std::string& filename) {
    m_writer->openFileWriter(filename);
}

void MainControl::setKmergen(InterfaceKmergen* kmergen) {
    m_kmergen = kmergen;
}

void MainControl::setCompare(InterfaceCompare* compare) {
    m_compare = compare;
}

void MainControl::setClust(InterfaceClust* clust) {
    m_clust = clust;
}
