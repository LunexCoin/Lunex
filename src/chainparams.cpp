// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2018 The Lunex Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Virtual Reality as sharp as the human eye can see.";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 262800; // Blocks per year
        consensus.nMasternodePaymentsStartBlock = 50; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 25000; // increase after 25k block
        consensus.nMasternodePaymentsIncreasePeriod = 26000; // increase every 13k blocks
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 3000000000; 
        consensus.nBudgetPaymentsCycleBlocks = 28800; // ~(60*24*30)/1.5
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 3000000000; // 
        consensus.nSuperblockCycle = 28800; // ~(60*24*30)/1.5
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x00000addc7843f4febe1850ff1602af6f7fca2fc3c8cefaeceb2b9c0e5f404dd"); 
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Lunex: 1 day
        consensus.nPowTargetSpacing = 2 * 60; // Lunex: 120 seconds
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowDGWHeight = 25;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800; // Feb 5th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800; // Feb 5th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1508025600; // Oct 15th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1539561600; // Oct 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100000"); 

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); // always verify

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xea;
        pchMessageStart[1] = 0xe3;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0x28;
        vAlertPubKey = ParseHex("0454653784503c81a4a8e0f15b884e0acbdf722b6c3959165c1c058a49466e41c7a16803c012d4ac357ebb2df47ddaaa4061420f9db3455dc567baa2962073aa48");
        nDefaultPort = 10050;
        nMaxTipAge = 24 * 60 * 60;
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1521788533, 4541190, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x00000335ce2d9c773a8c5a99d34adecba482388c232b7c2fe9ed254460bfceb2"));
        assert(genesis.hashMerkleRoot == uint256S("0x6aa7687ec7cdb3c9e2252e6f67943fb8c90ee293148bccdbcebeaad8fa4ea4a9"));
        
        vSeeds.push_back(CDNSSeedData("seed1.lunexcrypto.com", "seed1.lunexcrypto.com"));
 
        // Lunex addresses start with 'L'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,48);
        // Lunex script addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,125);
        // Lunex private keys start with 'm'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,110);
        // Lunex BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Lunex BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Lunex BIP44 coin type is '5'
        nExtCoinType = 5;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "04b0e1dae477b4fbe83b3198beb261135c26e0613edae90caa396cf48ec6b988a3dcf37a4bb39e526b3ec165fd878b8500a169eda4073d023ab3bfd4e660fe7852";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x00000335ce2d9c773a8c5a99d34adecba482388c232b7c2fe9ed254460bfceb2"))
			(  1, uint256S("0x00000df9543c1350699450c481ac256f5ab136a6257706727b0458cba8467200"))
			( 71, uint256S("0x000003a738248712daad3194c3586e6f91f1087045280781a290145dc28fc3b5")),
            1521896400, // * UNIX timestamp of last checkpoint block
            71,		// * total number of transactions between genesis and last checkpoint
			//   (the tx=... number in the SetBestChain debug.log lines)
            500		// * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 350400; // Blocks per year
        consensus.nMasternodePaymentsStartBlock = 1024; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 40320; // increase after 6 weeks first
        consensus.nMasternodePaymentsIncreasePeriod = 26880; // increase every 4 weeks afterwards
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 3000000000;
        consensus.nBudgetPaymentsCycleBlocks = 28800;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 3000000000;
        consensus.nSuperblockCycle = 28800; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x0000095981c16c629ffafa06d096d686486a7698d9ba14db7dfa72fd4a6a36de");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Lunex: 1 day
        consensus.nPowTargetSpacing = 1.5 * 60; // Lunex: 1.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowDGWHeight = 25; // activate DGW early
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1506556800; // September 28th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1538092800; // September 28th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1505692800; // Sep 18th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1537228800; // Sep 18th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 50; // 50% of 100

        // The best chain should have at least this much work.
        // not used currently
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100000"); 

        // By default assume that the signatures in ancestors of this block are valid.
        // not used currently
        consensus.defaultAssumeValid = uint256S("0x00"); // always verify

        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 18800;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 24 * 60 * 60 * 14;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1521788533, 4541190, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x00000335ce2d9c773a8c5a99d34adecba482388c232b7c2fe9ed254460bfceb2"));
        assert(genesis.hashMerkleRoot == uint256S("0x6aa7687ec7cdb3c9e2252e6f67943fb8c90ee293148bccdbcebeaad8fa4ea4a9"));
        
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("test1.lunexcrypto.com", "test2.lunexcrypto.com"));

        // Testnet Lunex addresses start with 'y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,140);
        // Testnet Lunex script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet Lunex BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Lunex BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet Lunex BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04cbd9d9d7e86a0b34fa0ac7da2d97ea036f0904914cf4c2ab924b242ba23a18bcd31adce63f244d91a5b496604b33b5a46b95069469dec2377be8a2dc2e02de7d";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (      0, uint256S("0x00000335ce2d9c773a8c5a99d34adecba482388c232b7c2fe9ed254460bfceb2")),
            1521788533, // * UNIX timestamp of last checkpoint block
            0,		// * total number of transactions between genesis and last checkpoint
			//   (the tx=... number in the SetBestChain debug.log lines)
            100		// * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Lunex: 1 day
        consensus.nPowTargetSpacing = 2.5 * 60; // Lunex: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nPowDGWHeight = 25;  
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); // always verify

        pchMessageStart[0] = 0x23;
        pchMessageStart[1] = 0x9a;
        pchMessageStart[2] = 0x46;
        pchMessageStart[3] = 0x12;
        nMaxTipAge = 24 * 60 * 60;
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 28800;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1521788533, 4541190, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x00000335ce2d9c773a8c5a99d34adecba482388c232b7c2fe9ed254460bfceb2"));
        assert(genesis.hashMerkleRoot == uint256S("0x6aa7687ec7cdb3c9e2252e6f67943fb8c90ee293148bccdbcebeaad8fa4ea4a9"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x00000335ce2d9c773a8c5a99d34adecba482388c232b7c2fe9ed254460bfceb2")),
            1521788533,
            0,
            0
        };
        // Regtest Lunex addresses start with 'y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,140);
        // Regtest Lunex script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Regtest Lunex BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Lunex BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest Lunex BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
