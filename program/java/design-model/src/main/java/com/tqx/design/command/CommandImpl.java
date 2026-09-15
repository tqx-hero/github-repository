package com.tqx.design.command;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/25 17:46
 */
public class CommandImpl implements Command {

    private Worker worker;

    public Command setWorker(Worker worker) {
        this.worker = worker;
        return this;
    }

    @Override
    public void execute() {
        worker.doWork();
    }

    @Override
    public void cancel() {
        worker.rest();
    }
}
