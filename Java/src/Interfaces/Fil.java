package Interfaces;

import objects.AuxStruct;
import objects.Venda;
import java.util.Set;

public interface Fil {

    Set<Venda> getFilial();

    void setFilial(Set<Venda> filial);

    void addVenda(Venda v);

    Set<Venda> filtrarVendasMes(int mes);

    Set<AuxStruct> query7();

}
