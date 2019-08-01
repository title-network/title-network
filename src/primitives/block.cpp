// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/block.h"

#include "arith_uint256.h"
#include "chainparams.h"
#include "crypto/common.h"
#include "hash.h"
#include "hash_blake2.h"
#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

uint256 CBlockHeader::GetHash() const {
    return SerializeHash(*this);
}

uint256 CBlockHeader::GetPoWHash(const int nHeight, const int nPowBlake2bHeight) const {
    if (nHeight >= nPowBlake2bHeight) {
        uint256 rc = Blake2::SerializeHash(*this);
        if ((nVersion == 0x21000000) &&
            (nHeight <= Params().GetConsensus().plug0x21ExploitHeight)) {
            arith_uint256 bnPoW;
            bnPoW.SetHex(rc.ToString());
            bnPoW /= 4295032833;
            rc.SetHex(bnPoW.GetHex());
        }

        return rc;
   }

   return GetHash();
}

std::string CBlock::ToString() const {
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, "
                   "hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, "
                   "vtx=%u)\n",
                   GetHash().ToString(), nVersion, hashPrevBlock.ToString(),
                   hashMerkleRoot.ToString(), nTime, nBits, nNonce, vtx.size());
    for (unsigned int i = 0; i < vtx.size(); i++) {
        s << "  " << vtx[i]->ToString() << "\n";
    }
    return s.str();
}
