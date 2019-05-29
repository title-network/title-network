# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

BITCOIN_CONFIG_INCLUDES=-I$(builddir)/config
BITCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

BITCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
BITCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

TITLE_SEEDER_INCLUDES = -I$(srcdir)/seeder
TITLE_SEEDER_INCLUDES += $(BITCOIN_INCLUDES)

LIBTITLE_SERVER=libtitle_server.a
LIBTITLE_COMMON=libtitle_common.a
LIBTITLE_CONSENSUS=libtitle_consensus.a
LIBTITLE_CLI=libtitle_cli.a
LIBTITLE_UTIL=libtitle_util.a
LIBTITLE_CRYPTO=crypto/libtitle_crypto.a
LIBTITLEQT=qt/libtitleqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBTITLE_ZMQ=libtitle_zmq.a
endif
if BUILD_TITLE_LIBS
LIBTITLECONSENSUS=libtitleconsensus.la
endif
if BUILD_TITLE_SEEDER
LIBTITLE_SEEDER=libtitle_seeder.a
endif
if ENABLE_WALLET
LIBTITLE_WALLET=libtitle_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBTITLE_CRYPTO) \
  $(LIBTITLE_UTIL) \
  $(LIBTITLE_COMMON) \
  $(LIBTITLE_CONSENSUS) \
  $(LIBTITLE_SERVER) \
  $(LIBTITLE_CLI) \
  $(LIBTITLE_SEEDER) \
  $(LIBTITLE_WALLET) \
  $(LIBTITLE_ZMQ)

lib_LTLIBRARIES = $(LIBTITLECONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_TITLED
  bin_PROGRAMS += titled
endif

if BUILD_TITLE_SEEDER
  bin_PROGRAMS += title-seeder
endif

if BUILD_TITLE_UTILS
  bin_PROGRAMS += title-cli title-tx
endif

.PHONY: FORCE check-symbols check-security
# bitcoin abcd #
BITCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  cashaddr.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  config.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  globals.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  pow.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/misc.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/scriptcache.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/finaltx.h \
  wallet/rpcdump.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libtitle_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between titled and title-qt
libtitle_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libtitle_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_server_a_SOURCES = \
  addrman.cpp \
  addrdb.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  config.cpp \
  globals.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/abc.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/scriptcache.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(BITCOIN_CORE_H)

if ENABLE_ZMQ
libtitle_zmq_a_CPPFLAGS = $(BITCOIN_INCLUDES) $(ZMQ_CFLAGS)
libtitle_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between titled and title-qt, but only linked
# when wallet enabled
libtitle_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libtitle_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/finaltx.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  $(BITCOIN_CORE_H)

# crypto primitives library
crypto_libtitle_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_CONFIG_INCLUDES)
crypto_libtitle_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libtitle_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# consensus: shared between all executables that validate any consensus rules.
libtitle_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libtitle_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  hash_blake2.cpp \
  hash_blake2.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/titleconsensus.cpp \
  script/sighashtype.h \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between titled, and title-qt and non-server tools
libtitle_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libtitle_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  cashaddr.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(BITCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libtitle_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libtitle_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libtitle_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between title-cli and title-qt
libtitle_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libtitle_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_cli_a_SOURCES = \
  rpc/client.cpp \
  $(BITCOIN_CORE_H)

# seeder library
libtitle_seeder_a_CPPFLAGS = $(AM_CPPFLAGS) $(PIE_FLAGS) $(TITLE_SEEDER_INCLUDES)
libtitle_seeder_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libtitle_seeder_a_SOURCES = \
  seeder/bitcoin.cpp \
  seeder/bitcoin.h \
  seeder/compat.h \
  seeder/db.cpp \
  seeder/db.h \
  seeder/dns.c \
  seeder/dns.h \
  seeder/netbase.cpp \
  seeder/netbase.h \
  seeder/protocol.cpp \
  seeder/protocol.h \
  seeder/strlcpy.h \
  seeder/util.cpp \
  seeder/util.h

nodist_libtitle_util_a_SOURCES = $(srcdir)/obj/build.h
#

# titled binary #
titled_SOURCES = titled.cpp
titled_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
titled_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
titled_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
titled_SOURCES += titled-res.rc
endif

titled_LDADD = \
  $(LIBTITLE_SERVER) \
  $(LIBTITLE_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBTITLE_UTIL) \
  $(LIBTITLE_WALLET) \
  $(LIBTITLE_ZMQ) \
  $(LIBTITLE_CONSENSUS) \
  $(LIBTITLE_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

titled_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# title-cli binary #
title_cli_SOURCES = title-cli.cpp
title_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
title_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
title_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
title_cli_SOURCES += title-cli-res.rc
endif

title_cli_LDADD = \
  $(LIBTITLE_CLI) \
  $(LIBUNIVALUE) \
  $(LIBTITLE_UTIL) \
  $(LIBTITLE_CRYPTO)

title_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# title-seeder binary #
title_seeder_SOURCES = seeder/main.cpp
title_seeder_CPPFLAGS = $(AM_CPPFLAGS) $(TITLE_SEEDER_INCLUDES)
title_seeder_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
title_seeder_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

title_seeder_LDADD = \
  $(LIBTITLE_SEEDER) \
  $(LIBTITLE_UTIL) \
  $(LIBTITLE_CRYPTO)

title_seeder_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)
#

# title-tx binary #
title_tx_SOURCES = title-tx.cpp
title_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
title_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
title_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
title_tx_SOURCES += title-tx-res.rc
endif

title_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBTITLE_COMMON) \
  $(LIBTITLE_UTIL) \
  $(LIBTITLE_CONSENSUS) \
  $(LIBTITLE_CRYPTO) \
  $(LIBSECP256K1)

title_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# titleconsensus library #
if BUILD_TITLE_LIBS
include_HEADERS = script/titleconsensus.h
libtitleconsensus_la_SOURCES = $(crypto_libtitle_crypto_a_SOURCES) $(libtitle_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libtitleconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libtitleconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libtitleconsensus_la_LIBADD = $(LIBSECP256K1)
libtitleconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL
libtitleconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CBLAKE2_DIST = crypto/cblake2/blake2-impl.h
CBLAKE2_DIST += crypto/cblake2/blake2.h
CBLAKE2_DIST += crypto/cblake2/blake2b-ref.c
CBLAKE2_DIST += crypto/cblake2/blake2bp-ref.c
CBLAKE2_DIST += crypto/cblake2/blake2s-ref.c
CBLAKE2_DIST += crypto/cblake2/blake2sp-ref.c
CBLAKE2_DIST += crypto/cblake2/blake2xb-ref.c
CBLAKE2_DIST += crypto/cblake2/blake2xs-ref.c
CBLAKE2_DIST += crypto/cblake2/genkat-c.c
CBLAKE2_DIST += crypto/cblake2/genkat-json.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST) $(CBLAKE2_DIST)

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
