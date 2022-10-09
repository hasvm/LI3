package objects;

import Interfaces.CatProd;

import java.io.Serializable;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;


public class CatalogoProdutos implements CatProd, Serializable {

        /**variavies de instancia*/
        private Set<Produto> catP;

        /**construtores*/
        public CatalogoProdutos() {

            this.catP = new TreeSet<Produto>();
        }


        public CatalogoProdutos(TreeSet<Produto> catP) {

            this.catP = catP.stream().map(c -> c.clone()).collect(Collectors.toCollection(TreeSet::new));
        }

        public CatalogoProdutos(CatalogoProdutos catP){

            this.catP = catP.getCatCopy();
        }

        /**metodos(gets/sets/adds)*/
        public Set<Produto> getCatP() {

            return this.catP;
        }

        public Set<Produto> getCatCopy(){

            return this.catP.stream().map(c->c.clone()).collect(Collectors.toCollection(TreeSet::new));
        }

        public Set<String> getCatCodCopy(){

            return this.catP.stream().map(c->c.getCod()).collect(Collectors.toCollection(TreeSet::new));
        }

        public void setCatP(Set<Produto> catP) {

            this.catP = catP.stream().map(c -> c.clone()).collect(Collectors.toCollection(TreeSet::new));;
        }

        public void addProduto(Produto p){

            this.catP.add(p.clone());
        }

        public boolean exists(Produto p){

            return this.catP.contains(p);
        }

        /**metodo clone*/
        public CatalogoProdutos clone(){

            return new CatalogoProdutos(this);
        }

        public int totalPrds(){
            return this.catP.size();
        }

        /**metodo equals*/
        @Override
        public boolean equals(Object o) {

            if (this == o) return true;
            if (!(o instanceof CatalogoProdutos)) return false;
            CatalogoProdutos that = (CatalogoProdutos) o;
            return getCatP().equals(that.getCatP());
        }

        /**metodo toString*/
        @Override
        public String toString() {

            StringBuilder s = new StringBuilder();
            for(Produto p : this.catP){
                s.append(p.toString());
            }
            return s.toString();
        }
}
