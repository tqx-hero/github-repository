package com.tqx.design.command;

public interface Command {
    void execute();

    void cancel();

    Command setWorker(Worker worker);
}
