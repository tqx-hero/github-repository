package com.tqx.design.command;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/25 17:48
 */
public class CaptionInvoker implements CommandInvoker {

    private Command command;

    @Override
    public CommandInvoker addCommand(Command command) {
        this.command = command;
        return this;
    }

    @Override
    public void pressButton() {
        command.execute();
    }

    @Override
    public void undoButton() {
        command.cancel();
    }
}
