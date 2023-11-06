package pop3.server.state;

import pop3.server.Pop3Session;

public class AuthorizationState extends Pop3SessionState {
    private String username;
    private String password;

    public AuthorizationState(Pop3Session session) {
        super(session);
        super.session.sendPositive();
    }

    @Override
    public void capa(String[] arguments) {
        super.session.sendPositive("");
        super.session.sendResponse("USER");
        super.session.sendResponse("PASS");
        super.session.sendResponse(".");
    }

    @Override
    public void user(String[] arguments) {
        if (arguments.length != 2 || arguments[1].isBlank() || this.username != null) {
            this.username = null;
            super.session.sendNegative();
        } else {
            this.username = arguments[1];
            super.session.sendPositive();
        }
    }

    @Override
    public void pass(String[] arguments) {
        if (arguments.length != 2 || arguments[1].isBlank() || this.username == null) {
            this.username = null;
            super.session.sendNegative();
        } else {
            this.password = arguments[1];
            super.session.sendPositive();
            super.session.setState(new TransactionState(super.session));
        }
    }

    @Override
    public void stat(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void list(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void retr(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void dele(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void noop(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void rset(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void quit(String[] arguments) {
        // Close socket:
        super.session.close();
    }
}