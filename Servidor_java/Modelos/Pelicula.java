package Servidor_java.Modelos;

public class Pelicula extends Produto{

    private String modelo;
    private String material;
    

    public Pelicula(int id,String nome,String descricao,double preco,int estoque,String modelo,String material){

        super(id,nome,descricao,preco,estoque);

        this.modelo = modelo;
        this.material = material;
    }

    public String getModelo(){return modelo;}
    public String getMaterial(){return material;}

    public void setModelo(String modelo){this.modelo = modelo;}
    public void setMaterial(String material){this.material = material;}

    public String toString() {
        return "Capinha [id=" + getId() + ", nome=" + getNome() + ", preco=" + getPreco() + ", estoque=" + getEstoque() + "modelo="+ modelo + "material="+ material +"]";
    }


}
