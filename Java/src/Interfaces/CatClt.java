package Interfaces;

import objects.Cliente;
import java.util.Set;


public interface CatClt {

    Set<Cliente> getCatC();

    void setCatC(Set<Cliente> catC) ;

    void addCliente(Cliente c);

    boolean exists(Cliente c);

    int totalClts();
}
