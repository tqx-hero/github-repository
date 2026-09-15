package com.tqx.design.command;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/25 17:49
 */
public class Test {

    public static void main(String[] args) {
        Worker worker = new MatouWorker();
        Command command = new CommandImpl().setWorker(worker);
        CommandInvoker invoker = new CaptionInvoker().addCommand(command);
        invoker.pressButton();
        invoker.undoButton();
    }
}
