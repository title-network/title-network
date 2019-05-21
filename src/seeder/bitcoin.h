#ifndef TITLE_SEEDER_BITCOIN_H
#define TITLE_SEEDER_BITCOIN_H

#include "protocol.h"

bool TestNode(const CService &cip, int &ban, int &client, std::string &clientSV,
              int &blocks, std::vector<CAddress> *vAddr);

#endif
