package pop3.server;

import pop3.server.state.AuthorizationState;
import pop3.server.state.Pop3SessionState;

import java.io.*;
import java.net.Socket;

public class Pop3Session implements Runnable {
    private final Socket serverSocket;
    private Pop3SessionState currentState;
    private BufferedReader inputReader;
    private BufferedWriter outputWriter;

    public Pop3Session(Socket serverSocket) {
        this.serverSocket = serverSocket;
    }

    @Override
    public void run() {
        try {
            this.inputReader = new BufferedReader(new InputStreamReader(this.serverSocket.getInputStream()));
            this.outputWriter = new BufferedWriter(new OutputStreamWriter(this.serverSocket.getOutputStream()));
            this.currentState = new AuthorizationState(this);
            while (!this.serverSocket.isClosed()) {
                this.handleCommand();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (this.outputWriter != null) {
                    this.outputWriter.close();
                }
                if (this.inputReader != null) {
                    this.inputReader.close();
                }
                serverSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void close() {
        try {
            this.serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void setState(Pop3SessionState newState) {
        this.currentState = newState;
    }

    public String readCommand() {
        try {
            var command = this.inputReader.readLine();
            System.out.println(command);
            return command;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void handleCommand() {
        var command = this.readCommand().split(" ");
        switch (command[0]) {
            case "CAPA":
                this.currentState.capa(command);
                break;
            case "USER":
                this.currentState.user(command);
                break;
            case "PASS":
                this.currentState.pass(command);
                break;
            case "STAT":
                this.currentState.stat(command);
                break;
            case "LIST":
                this.currentState.list(command);
                break;
            case "RETR":
                this.currentState.retr(command);
                break;
            case "DELE":
                this.currentState.dele(command);
                break;
            case "NOOP":
                this.currentState.noop(command);
                break;
            case "RSET":
                this.currentState.rset(command);
                break;
            case "QUIT":
                this.currentState.quit(command);
                break;
            default:
                this.sendNegative();
        }
    }

    public void sendResponse(String message) {
        try {
            System.out.println(message);
            this.outputWriter.write(message + "\r\n");
            this.outputWriter.flush();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void sendPositive() {
        this.sendResponse("+OK Everything alright.");
    }

    public void sendPositive(String message) {
        this.sendResponse("+OK " + message);
    }

    public void sendNegative() {
        this.sendResponse("-ERR Something went wrong.");
    }

    public void sendNegative(String message) {
        this.sendResponse("+ERR " + message);
    }
}