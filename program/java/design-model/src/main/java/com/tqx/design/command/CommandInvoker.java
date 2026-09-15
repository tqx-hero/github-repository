package com.tqx.design.command;

public interface CommandInvoker {

    CommandInvoker addCommand(Command command);

    void pressButton();

    void undoButton();

}
