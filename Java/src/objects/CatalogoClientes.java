package objects;

import Interfaces.CatClt;

import java.io.Serializable;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class CatalogoClientes implements CatClt, Serializable {

    /**variaveis de instancia*/
    private Set<Cliente> catC;

    /**construtores*/
    public CatalogoClientes() {

        this.catC = new TreeSet<Cliente>();
    }


    public CatalogoClientes(TreeSet<Cliente> catC) {

        this.catC = catC.stream().map(c -> c.clone()).collect(Collectors.toCollection(TreeSet::new));
    }

    public CatalogoClientes(CatalogoClientes catC){

        this.catC = catC.getCatCopy();
    }

    /**metodos(gets/sets/adds)*/
    public Set<Cliente> getCatC() {

        return catC;
    }

    public Set<Cliente> getCatCopy(){

        return this.catC.stream().map(c->c.clone()).collect(Collectors.toCollection(TreeSet::new));
    }

    public void setCatC(Set<Cliente> catC) {

        this.catC = catC.stream().map(c->c.clone()).collect(Collectors.toCollection(TreeSet::new));
    }

    public void addCliente(Cliente c){

        this.catC.add(c.clone());
    }

    public boolean exists(Cliente c){

        return this.catC.contains(c);
    }

    /**metodo clone*/
    public CatalogoClientes clone(){

        return new CatalogoClientes(this);
    }

    public int totalClts(){
        return this.catC.size();
    }

    /**metodo equals*/
    @Override
    public boolean equals(Object o) {

        if (this == o) return true;
        if (!(o instanceof CatalogoClientes)) return false;
        CatalogoClientes that = (CatalogoClientes) o;
        return getCatC().equals(that.getCatC());
    }

    /**metodo toString*/
    @Override
    public String toString() {

        StringBuilder s = new StringBuilder();
        for(Cliente c : this.catC){
            s.append(c.toString());
        }
        return s.toString();
    }
}
