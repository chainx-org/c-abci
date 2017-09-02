# c-abci
This library use C language  to implement **Tendermint ABCI**. It provides three interfaces and that's all you need to code a application's framework， very easy to start on！

You can get C-ABCI's source code from github:[https://github.com/chainx-org/c-abci]

For show you how to use this **C-ABCI** library，I implement a very simple demo application which calls **c-dummy** in **demo** directory!


**c-dummy** runs as follow：

Step 1：
Intall **Tendermint** to your comptuer! [https://tendermint.com/docs/guides/install-from-source]

Step 2： Enter into **c-abci** directory and compile source code:
``` console
    cd c-abci
    make
```
Just as simple as this, the compilation of **c-abci** and **c-dummy** is completed! You will see **c-dummy** in **c-abci/bin** directory and **c-abci** in **c-abci/lib/** directory！

Step 3:Run **c-dummy**:
``` console
    cd bin
    ./c-dummy 127.0.0.1 46658
```
The parameters of **c-dummy** :'127.0.0.1 46658'  is 'proxy_app' field value from **~/.tendermint/config.toml** configure file of Tendermint .

Step 4: Run Tendermint node
If it's your first time to run **Tendermint**, you should excute the following commands:
``` console
    tendermint init
    tendermint node
```

If you had run it before, you should excute the following commands:
``` console
    tendermint unsafe_reset_all
    tendermint node
```
This is whole  procedure of run **c-dummy**, when you successfully done all the steps in above， you can see both c-dummmy's  and tendermint's terminal  streaming up data！

learn more about this program: xxxxxxxx

