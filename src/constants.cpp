#include <limits>
#include <stdint.h>

#include "bignum.h"
#include "macros.h"
#include "types.h"

uint16_t      COIN_PORT               = 7742;
uint16_t      RPC_PORT                = 7743;

//            These bytes are put at the beginning of every packet, and should be unique to a coin network
//            They are designed to be unlikely to occur in normal data. The characters are rarely used upper ascii, not valid as UTF-8, and produce a large 4-byte int at any alignment
uint8_t       PROTOCOL_MAGIC_BYTES[4] = { 0xe5, 0xcf, 0x81, 0xde };

//            These parameters are used as initial nodes to connect to, from which we will get the other ones
//            Each DNS pair gives a source name and a seed name. The first name is used as information source for addrman, and the second name should resolve to a list of seed addresses
//            The last element of each array has to be null (respectively { 0, 0 } and 0)
char const *  AUTO_DNS_SEEDS[][2]     = { { 0, 0 } };
uint32_t      AUTO_IP_SEEDS[]         = { 0 };

//            These numbers each map to a base58 character which is put in front of the addresses to easily deduce an address type
uint8_t       PUBKEY_ADDRESS_PREFIX   =  53; // "N"
uint8_t       PRVKEY_ADDRESS_PREFIX   =  52; // "M"
uint8_t       SCRIPT_ADDRESS_PREFIX   = 112; // "n"

//            The following constants define the genesis block of the coin network
//            If you change them, the hash will probably be wrong and the genesis invalid (because its hash would be higher than the initial target), and the client will try to generate a new valid genesis at startup
hash_t        GENESIS_HASH            = hash_t("0x000009b4cc9d78dd3d3da01579414ddeb90ffe1d8fdf1fc232f16e174aef8724");
char          GENESIS_IDENT[]         = "Matonis 07-AUG-2012 Parallel Currencies And The Roadmap To Monetary Freedom";
timestamp_t   GENESIS_TX_TIME         = 1345083810;
timestamp_t   GENESIS_BLOCK_TIME      = 1345084287;
uint32_t      GENESIS_BLOCK_NONCE     = 2179786789;
uint32_t      GENESIS_BLOCK_VERSION   = 1;

//            The maturity is the number of block required for a transaction to be confirmed by the network (excluding the block which embeds the transaction)
//            Since you need to include your transaction in a block, and the COINBASE_MATURITY cannot be lower than 1, you will always need at least two blocks before maturing
blockheight_t COINBASE_MATURITY       = 1;

//            Some parameters about the coin amount itself
//            If you use a non-zero COIN_PREMINE value, the first mined PoW block will have this reward. Otherwise, it will be POW_BLOCK_REWARD as usual
money_t       MAX_MONEY               = 500000000000 * COIN;
money_t       COIN_PREMINE            =   2000000000 * COIN;

//            If you submit a transaction to the network, you need to put at least MIN_TX_FEES coins for the client to accept it
//            You also need to put at least MIN_RELAY_TX_FEES, otherwise the other nodes will not relay it -
money_t       MIN_TX_FEES             = CENT;
money_t       MIN_RELAY_TX_FEES       = CENT;

//            The maximal amount of time drift allowed, after which the client will not accept old blocks
timestamp_t   MAX_CLOCK_DRIFT         = 2 * HOUR;

//            The maximal size of a block allowed by your coin network
uint32_t      MAX_BLOCK_SIZE          = 1000000;

//            Maximal number of PoW blocks, after which their reward become null
//            You can use std::numeric_limits< blockheight_t >::max( ) to disable this parameter
blockheight_t POW_MAX_BLOCK           = std::numeric_limits< blockheight_t >::max( );

//            Initial network targets
target_t      POW_INITIAL_TARGET      = target_t(~uint256(0) >> 20);
target_t      POS_INITIAL_TARGET      = target_t(~uint256(0) >> 20);

//            Maximal network targets (after which mining/minting a block won't be easier)
target_t      POW_MAX_TARGET          = target_t(~uint256(0) >> 20);
target_t      POS_MAX_TARGET          = target_t(~uint256(0) >> 20);

//            The average delay between two blocks
timestamp_t   POW_TARGET_SPACING      = 1 * MINUTE;
timestamp_t   POS_TARGET_SPACING      = 1 * MINUTE;

//            Reward for each PoW block mined, until POW_MAX_BLOCK (from which it will become null)
money_t       POW_BLOCK_REWARD        = 1000 * COIN;

//            The delay required for a coin to stake, and the delay after which a coin won't get any more bonuses
timestamp_t   STAKE_MIN_AGE           = 3 * MINUTE;
timestamp_t   STAKE_MAX_AGE           = 3 * MINUTE;

//            When calculating the coinage, we use STAKE_COIN_STEP and STAKE_AGE_STEP to respectively divide the coin number and coin age
money_t       STAKE_COIN_STEP         = 1 * COIN;
timestamp_t   STAKE_AGE_STEP          = 1 * DAY;

//            The target doesn't change immediately to take the new work difficulty in account - it is actually spread over an amount of time
timestamp_t   TARGET_TIMESPAN         = 10 * MINUTE;

// -- Be careful not to commit the checkpoint master key if you happen to use it
// -- Note that you should probably use the -checkpointkey command line parameter instead of using a modified client
// -- In order to generate a new valid checkpoint key, you have to use the `makekeypair` rpc command - don't try to generate it yourself

std::string   CHECKPOINT_PUBLIC_KEY   = "042f43a2e1e8185eb0f25380f4caa6de24d6a638ceb01374450207c9d25bfa586a20cc1295c686d20e090b324054aa4b93b405c9fea50df8bca0b70cca6b6758fc";
std::string   CHECKPOINT_PRIVATE_KEY  = ""; // don't put the private key here, use -checkpointkey instead

// -- These variables should probably not be modified, since they rely on the previous ones

money_t       MIN_TXOUT_AMOUNT        = MIN_TX_FEES;

uint32_t      MAX_BLOCK_SIZE_GEN      = MAX_BLOCK_SIZE / 2;
uint32_t      MAX_BLOCK_SIGOPS        = MAX_BLOCK_SIZE / 50;
uint32_t      MAX_BLOCK_ORPHAN_TX     = MAX_BLOCK_SIZE / 100;
