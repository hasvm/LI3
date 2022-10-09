package objects;

import Interfaces.Clt;

import java.io.Serializable;
import java.lang.*;

public class Cliente implements Comparable, Clt, Serializable {

        /**variavies de instancia*/
        private String cod;

        /**construtores*/
        public Cliente(){

            this.cod = "";
        }

        public Cliente(String cod) {

            this.cod = cod;
        }

        public Cliente(Cliente p){

            this.cod = p.cod;
        }

        /**metodos(gets/sets)*/
        public String getCod() {

            return this.cod;
        }

        public void setCod(String cod) {

            this.cod = cod;
        }

        /**metodo equals*/
        @Override
        public boolean equals(Object o) {

            if (this == o) return true;
            if (!(o instanceof Cliente)) return false;
            Cliente Cliente = (Cliente) o;
            return getCod().equals(Cliente.getCod());
        }

        /**metodo clone*/
        public Cliente clone(){

            return new Cliente(this);
        }

        /**metodo toString*/
        @Override
        public String toString() {

            return  "cod=" +this.cod;
        }

        /**metodo de comparaçao*/
    @Override
    public int compareTo(Object o) {
            Cliente a = (Cliente) o;
            return this.getCod().compareTo(a.getCod());
        }
}
