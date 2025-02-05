// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2019 The Altbet Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "base58.h"
#include "libzerocoin/Params.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
(0, uint256("0x852bf462534c29c0039513f244dd9b80a581f7cddf81214fe4236b3866c4d41d"))
(3900, uint256("0xe4365fdf5eb4fe1e6d3cbc498aa42c560d167698972853b9bac69811a44ce591"))
(3950, uint256("0x7cef902d8a35d8f2f5ece98e2b248f2c52712713426d8b52b8dfbc1f36b028e2"))
(4000, uint256("0x368f2f3bdc5db7a940478645b94267595850dd2dbeaac8d1f9f41bdde53ad326"))
(4240, uint256("0xe74f53edf64c55d0a4ffd6f8e774c3460179b9df0b3c4586ab1168fa92cde639"))
(10390, uint256("0x732f9f981e12bc92ae553276df45bec79218fb68baaac86f08bd183c2ba3549c"))
(21500, uint256("0xd58ce6ced3ba2e5fd01cc9dde8dfbc2722de3ed78451e15e1e3811116c9e130b"));


static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
	1564951151, // * UNIX timestamp of last checkpoint block
    0,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
	94705         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x1"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1561995372,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1561995372,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

libzerocoin::ZerocoinParams* CChainParams::OldZerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
		pchMessageStart[0] = 0x2a; // A
		pchMessageStart[1] = 0x2b; // B
		pchMessageStart[2] = 0x3e; // E
		pchMessageStart[3] = 0x88; // T-8
        vAlertPubKey = ParseHex("0435401a5693de702378a538ad939ea03b5e3b2826f68431ba840df5f418e3f3e8590ba4fb0c36097179bb55ffc4a4e065dc2ff87edb6f3ce4232a71d253ed7fff");
        nDefaultPort = 8322;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Altbet starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;

        nTargetTimespan = 1 * 60; // Altbet: 1 day
        nTargetSpacing = 120; // Altbet: 2 minute
        nLastPOWBlock = 220;
        nZerocoinStartHeight = INT_MAX;
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMasternodeCollateralAmt = 10000;
        nMasternodeCollateralAmtNew = 15000;
        nMinStakeInput = 30 * COIN;
        nModifierUpdateBlock = 1238900;
        nMaxMoneyOut = 21000000 * COIN;
        const char* pszTimestamp = "Winner, winner chicken dinner.";

        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e219a879b053d19f67f06f8f0b409d6dd3ce854db1c384c68990474ff1da4e6b2f55dd5ebeb176a8f271a11d898ee5f129066481b0ae8eeaab8d6c4a61d6e2fe") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1561995372;
        genesis.nBits = 504365040;
        genesis.nNonce = 1271976;

        hashGenesisBlock = genesis.GetHash();
        //printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(hashGenesisBlock == uint256("0x852bf462534c29c0039513f244dd9b80a581f7cddf81214fe4236b3866c4d41d"));
        assert(genesis.hashMerkleRoot == uint256("0x73b17d2797b7b4d0a6fe09204aa736b6c1d290d3a6a6f944b7eab02f7029d0af"));

        vSeeds.push_back(CDNSSeedData("140.82.48.162", "140.82.48.162"));
        vSeeds.push_back(CDNSSeedData("8.9.36.49", "8.9.36.49"));
		vSeeds.push_back(CDNSSeedData("95.179.149.133", "95.179.149.133"));
		vSeeds.push_back(CDNSSeedData("108.61.211.2", "108.61.211.2"));
		vSeeds.push_back(CDNSSeedData("45.63.85.96", "45.63.85.96"));
		vSeeds.push_back(CDNSSeedData("140.82.1.78", "140.82.1.78"));
		vSeeds.push_back(CDNSSeedData("140.82.48.162", "140.82.48.162"));
		vSeeds.push_back(CDNSSeedData("45.63.88.175", "45.63.88.175"));
		vSeeds.push_back(CDNSSeedData("149.28.203.191", "149.28.203.191"));
		vSeeds.push_back(CDNSSeedData("116.203.176.91", "116.203.176.91"));
		vSeeds.push_back(CDNSSeedData("45.76.11.89", "45.76.11.89"));
		vSeeds.push_back(CDNSSeedData("144.202.107.249", "144.202.107.249"));
		vSeeds.push_back(CDNSSeedData("136.244.104.7", "136.244.104.7"));
		vSeeds.push_back(CDNSSeedData("104.207.148.137", "104.207.148.137"));
		vSeeds.push_back(CDNSSeedData("95.216.79.235", "95.216.79.235"));
		vSeeds.push_back(CDNSSeedData("144.202.107.249", "144.202.107.249"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23); // A
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); // B
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 33);     // E
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
		//  BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

		bech32_hrp = "ab";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;

        nEnforceNewSporkKey = 1563578985; //07/19/2019 @ 11:29pm (UTC)
        nRejectOldSporkKey = 1563753600; //07/22/2019 @ 12:00am (UTC)
		
		strSporkKey = "032b46812dedb731d515b4fe28efd6591adcae691f03fb1577f1a6fb1c89f67ba2";
        strSporkKeyOld = "0239efda1c4227d678db60478f4a00bd2b90210805fe3faa91f8edec9f6a545dd1";
        strObfuscationPoolDummyAddress = "Ab5bNTKMKVJWLTDCwwEEvHH9MzDhxRaL5a";
        nStartMasternodePayments = 1561995372;

        /** Zerocoin */
		/* This is not active */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                          "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                          "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                          "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                          "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                          "31438167899885040445364023527381951378636564391212010397122822120720357";

        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
		
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};

static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x5e;
        pchMessageStart[3] = 0x78;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 39795;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Altbet: 1 day
        nTargetSpacing = 1 * 60;  // Altbet: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 1;
        nMasternodeCountDrift = 4;
        nMasternodeCollateralAmt = 1000;
        nMasternodeCollateralAmtNew = 5000;
        nMinStakeInput = 15 * COIN;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = INT_MAX;
        nZerocoinLastOldParams = INT_MAX;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1561995372;
        genesis.nNonce = 1271976;

		//printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x852bf462534c29c0039513f244dd9b80a581f7cddf81214fe4236b3866c4d41d"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet altbet addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet altbet script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet altbet BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet altbet BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet altbet BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tv";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 2;
        strSporkKey = "023bdfaa1671a451ebb3fdf4978c7336ce9283f35733006bfe059da6cd195ecf69";

        strObfuscationPoolDummyAddress = "Ab5bNTKMKVJWLTDCwwEEvHH9MzDhxRaL5a";
        nStartMasternodePayments = 1561995372;
	}
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x53;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x40;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Altbet: 1 day
        nTargetSpacing = 1 * 60;        // Altbet: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1561995372;
        genesis.nBits = 504365040;
        genesis.nNonce = 1271976;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nZerocoinLastOldParams = 499;
        nZerocoinStartHeight = 100;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 39793;
        //assert(hashGenesisBlock == uint256("0x852bf462534c29c0039513f244dd9b80a581f7cddf81214fe4236b3866c4d41d"));


        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        nRequiredAccumulation = 1;

        // {
        //     "PrivateKey": "923EhWh2bJHynX6d4Tqt2Q75bhTDCT1b4kff3qzDKDZHZ6pkQs7",
        //     "PublicKey": "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a"
        // }
        strSporkKey = "04cded1204a57acd6280c8499b7a2df052609dbf96546453984d632204d651d72a37013edc9d115e5a385e100eb7e867923fdd0bb7d9dc31aa1eb9d59b00c76697";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 39791;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
