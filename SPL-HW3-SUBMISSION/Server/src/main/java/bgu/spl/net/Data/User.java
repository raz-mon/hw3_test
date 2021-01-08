package bgu.spl.net.Data;

public abstract class User {
    private final String username;
    private final String password;
    private boolean loggedIn;

    public User(String username, String password){
        this.username = username;
        this.password = password;
        this.loggedIn = false;
    }

    public String getUsername(){
        return this.username;
    }

    public String getPassword(){
        return this.password;
    }

    public boolean isLoggedIn(){
        return this.loggedIn;
    }

    public void setLoggedIn(boolean b){
        loggedIn = b;
    }
}

