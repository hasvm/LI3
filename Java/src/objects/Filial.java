package objects;

import Interfaces.Fil;
import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe Filial
 */

public class Filial implements Fil, Serializable {

/**variáveis de instância*/

    private Set<Venda> filial;

/**construtores*/

    public Filial(){

        this.filial = new HashSet<Venda>();
    }
    public Filial(Set<Venda> filial) {

        this.filial = filial.stream().map(f -> f.clone()).collect(Collectors.toCollection(HashSet::new));;
    }

    public Filial(Filial f){

        this.filial = f.getCopy();
    }

    /**devolve cópia da filial*/
    public Set<Venda> getCopy(){

        return this.filial.stream().map(f -> f.clone()).collect(Collectors.toCollection(HashSet::new));
    }

    /**devolve filial*/
    public Set<Venda> getFilial() {

        return filial;
    }

    /**determinar filial*/
    public void setFilial(Set<Venda> filial) {

        this.filial = filial.stream().map(f -> f.clone()).collect(Collectors.toCollection(HashSet::new));
    }

    /**adicionar venda a filial*/
    public void addVenda(Venda v){

        this.filial.add(v.clone());
    }

    /**filtra vendas*/
    public Set<Venda> filtrarVendasMes(int mes){

        Set<Venda> ret = this.filial.stream().filter(v -> v.getMes()==mes).map(v->v.clone()).collect(Collectors.toCollection(HashSet::new));
        return ret;
    }

    public Set<AuxStruct> query7(){

        Map<String,AuxStruct> aux = new HashMap<>();
        for(Venda v : this.filial){
            if(aux.containsKey(v.getClt().getCod())){
                aux.get(v.getClt().getCod()).incQuant(v.getQuant()*v.getPreco());
            }
            else{
                aux.put(v.getClt().getCod(),new AuxStruct(v.getPreco()*v.getQuant(),v.getClt().getCod()));
            }
        }
        return aux.values().stream().limit(3).collect(Collectors.toCollection(TreeSet::new));
    }


    public Filial clone(){

        return new Filial(this);
    }

    @Override
    public boolean equals(Object o) {

        if (this == o) return true;
        if (!(o instanceof Filial)) return false;
        Filial filial1 = (Filial) o;
        return getFilial().equals(filial1.getFilial());
    }

    @Override
    public String toString() {

       StringBuilder s = new StringBuilder();
       for(Venda v : this.filial) {
           s.append(v.toString());
       }
       return s.toString();
    }
}
