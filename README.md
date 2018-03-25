# Lunex Core staging tree 0.12.2
<p align="center">
<a href="https://travis-ci.org/lunexcrypto/lunex" alt="Build Status">
<img src="https://travis-ci.org/lunexcrypto/lunexcoin.svg?branch=master"/>
</a>
<a href="https://github.com/lunexcrypto/lunexcoin/releases" alt="GIT Releases">
<img src="https://img.shields.io/github/downloads/lunexcoin/lunex/total.svg"/>
</a>
<a href="https://discord.lunexcrypto.com" alt="Discord">
<img src="https://img.shields.io/discord/402827967111233546.svg"/>
  </a>
<a href="https://twitter.lunexcrypto.com" alt="Twitter">
<img src="https://img.shields.io/twitter/follow/lunex_crypto.svg?style=social&label=Follow"/>
</a>
</p>
<p align="center">
  <a href="https://www.lunexcrypto.com">https://www.lunexcrypto.com</a> | <a href="https://explorer.lunexcrypto.com">Block Explorer</a> | <a href="https://ann.lunexcrypto.com">Announcement</a> | <a href="https://discord.lunexcrypto.com">Discord</a> | <a href="https://twitter.lunexcrypto.com">Twitter</a>
</p>

## About Lunex

LUNEX offers highly secured, anonymous transactions across the world. LUNEX supports Masternodes with a superb block reward. Features as Private Send and Instant Send make LUNEX a future-oriented currency on the market. LUNEX uses peer-to-peer technology to operate with no central authority: managing transactions and issuing money are carried out collectively by the network. Lunex Core is the name of the open source software which enables the use of this currency. Lunex Core is based on the newest [Dash](https://www.dash.org) codebase and is its own currency.

For more information, as well as an immediately useable, binary version of
the Lunex Core software, see https://www.lunexcrypto.com

## Lunex Specifications

| Specification | Value |
| ------ | ------ |
| PoW Algorithm | Lyra2REv2 |
| Block Time Average | 90 seconds |
| Block Reward | 8 LUNEX |
| Block Reward Distribution | 40% to Masternodes, 60% to Miners initially, ramping up to 65% Masternodes, 35% miners |
| Masternode Collateral | 1000 LUNEX |
| Estimated Supply | 32.7 Mio. |
| Difficulty Retargeting | Every block |
| Difficulty Algorithm | Dark Gravity Wave v3 | 

## License

Lunex Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

## Development Process

The `master` branch is meant to be stable. Development is normally done in separate branches.
[Tags](https://github.com/lunexcrypto/lunex/tags) are created to indicate new official,
stable release versions of Lunex Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

## Testing

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](/doc/unit-tests.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows
and Linux, OS X, and that unit and sanity tests are automatically run.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
