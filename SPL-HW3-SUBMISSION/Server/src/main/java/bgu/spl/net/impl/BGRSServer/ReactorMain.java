package bgu.spl.net.impl.BGRSServer;

import bgu.spl.net.srv.Reactor;
import bgu.spl.net.srv.ThreadPerClientServer;
import bgu.spl.net.srv.registrationMessageEncoderDecoder;
import bgu.spl.net.srv.registrationMessagingProtocol;

public class ReactorMain {
    public static void main(String[] args){
        Reactor<String> reactor = new Reactor<>(Integer.parseInt(args[1]),
                Integer.parseInt(args[0]),
                () -> new registrationMessagingProtocol(),
                () -> new registrationMessageEncoderDecoder());
        reactor.serve();
    }
}

