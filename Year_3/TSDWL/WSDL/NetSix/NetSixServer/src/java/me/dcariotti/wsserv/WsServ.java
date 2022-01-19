/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package me.dcariotti.wsserv;

import java.util.HashMap;
import javax.jws.WebService;
import javax.jws.WebMethod;
import javax.jws.WebParam;

/**
 *
 * @author dcariotti
 */
@WebService(serviceName = "WsServ")
public class WsServ {

    private HashMap<String, int[]> series;

    public WsServ() {
        this.series = new HashMap<String, int[]>();
        this.series.put("The Witcher", new int[] {1, 2, 3, 4, 5, 6});
        this.series.put("Rick & Morty", new int[] {1, 2, 3, 4, 5, 6, 7, 8});
        this.series.put("After Life", new int[] {1, 4, 5, 6, 9});
        this.series.put("Lovesick", new int[] {1, 2, 3, 4, 5, 6, 7});
        this.series.put("Chuck", new int[] {1, 2, 3, 4, 5, 6});
        this.series.put("Halt and catch fire", new int[] {1, 2, 3});
    }
    
    @WebMethod(operationName = "richiedi")
    public boolean richiedi(@WebParam(name = "name") final String name, @WebParam(name = "episode") final int episode) {
        if (this.series.containsKey(name)) {
            int[] episodes = this.series.get(name);

            for (int number : episodes) {
                if (number == episode) {
                    return true;
                }
            }
        }
        
        return false;
    }
}
