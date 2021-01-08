package bgu.spl.net.impl.BGRSServer;

import bgu.spl.net.srv.ThreadPerClientServer;
import bgu.spl.net.srv.registrationMessageEncoderDecoder;
import bgu.spl.net.srv.registrationMessagingProtocol;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class TPCMain {

    public static void main(String[] args) {

        ThreadPerClientServer TPCS = new ThreadPerClientServer(Integer.parseInt(args[0]),
                () -> new registrationMessagingProtocol(),
                () -> new registrationMessageEncoderDecoder());
        TPCS.serve();
    }


/*
        short x  = 500;
        byte[] b = shortToBytes(x);
        System.out.println(Arrays.toString(b));
        short y = bytesToShort(b);
        System.out.println(y);
    }

    public static byte[] shortToBytes (short num)
    {
        byte[] bytesArr = new byte[2];
        bytesArr[0] = (byte) ((num >> 8) & 0xFF);
        bytesArr[1] = (byte) (num & 0xFF);
        return bytesArr;
    }

    public static short bytesToShort (byte[] byteArr)
    {
        short result = (short) ((byteArr[0] & 0xff) << 8);
        result += (short) (byteArr[1] & 0xff);
        return result;
    }

 */

}
