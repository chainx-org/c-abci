# C-ABCI

A C implementation of the Tendermint Application BlockChain Interface ([ABCI](https://github.com/tendermint/abci)).

## Requirement

Install [Tendermint](https://tendermint.com/docs/guides/install-from-source)

## Getting Started

1. Clone this project and run `make`:

    ```bash
    $ git clone https://github.com/chainx-org/c-abci.git ~/c-abci
    $ cd ~/c-abci
    $ make
    ```

2. When `make` is done, you'll see an executale program `c-dummy` in the `bin` directory, run it:

    ```bash
    $ cd bin
    $ ./c-dummy
    ```

3. Start Tendermint.

    ```bash
    $ tendermint init
    $ tendermint node
    ```

    Note: if you have run Tendermint before, reset it first:

    ```bash
    $ tendermint unsafe_unset_all
    $ tendermint node
    ```
