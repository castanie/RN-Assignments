package pop3.server.state;

import pop3.server.Pop3Session;

public abstract class Pop3SessionState {
    protected final Pop3Session session;

    public Pop3SessionState(Pop3Session session) {
        this.session = session;
    }

    public abstract void capa(String[] arguments);

    public abstract void user(String[] arguments);

    public abstract void pass(String[] arguments);

    public abstract void stat(String[] arguments);

    public abstract void list(String[] arguments);

    public abstract void retr(String[] arguments);

    public abstract void dele(String[] arguments);

    public abstract void noop(String[] arguments);

    public abstract void rset(String[] arguments);

    public abstract void quit(String[] arguments);
}