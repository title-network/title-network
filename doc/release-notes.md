Title Network version 0.17.0 is now available from:

  <https://github.com/title-network/title-network/releases/tag/v0.17.0>

This release includes the following features and fixes:
- Blake2b PoW change from sha256
  - Hard fork at block height x mainnet (approximately @todo)
  - Hard fork at block height 248000 testnet (Jan 21st, 2019 14:24:00 GMT)
- Increase MAX_OP_RETURN_RELAY to 223 byte.

It also includes a full rebrand
- All references to Bitcoin Core (SQ) in the context of $BTCC has been removed.
- With great sadness references to Bitcoin Clashic (ABCD) has been removed.
- clashicd & clashic-XXX binaries now titled and title-XXX.
- Default datadir will be .tnet from .clashic
- The protocol and client implementation are now known as "Title Network".
- Symbol will be changed from $BTCC ($BCORE in some places) to $TNET.
- Github repo moved to title-network organization. bitcoin-cored organization will be sunset.

Initially Bitcoin Core SQ 0.16.2.2 and Title Network 0.17.0.0 will be compatible.
There will be no support of Bitcoin Core SQ 0.16.2.2 following the activation of Blake2b PoW at the above height on mainnet.
