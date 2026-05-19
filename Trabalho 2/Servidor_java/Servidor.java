package Servidor_java;

//import java.util.Properties;
import java.io.FileInputStream;

import org.omg.CORBA.ORB;
import org.omg.PortableServer.POA;
import org.omg.PortableServer.POAHelper;
import org.omg.CosNaming.*;

import Servidor_java.Modelos.*;
import Servidor_java.Servicos.CatalogoProdutos;

public class Servidor {
    public static void main(String args[]) {
        
        // 1. Prepara as suas classes de domínio locais
        CatalogoProdutos catalogo_Geral = new CatalogoProdutos();
        catalogo_Geral.AdicionarProduto(new Celular(1,"IPhone 15","Apple",5000.0,5,"Apple","15 Pro"));
        catalogo_Geral.AdicionarProduto(new Capa(2, "Capa Iphone", "Azul", 15, 20, "Iphone 15", "Plastico"));
        catalogo_Geral.AdicionarProduto(new Pelicula(3, "Pelicula","5 pol" , 25.50, 15, "Iphone 15", "Vidro"));
        catalogo_Geral.AdicionarProduto(new PowerBank(4,"Power Bank","Bateria",200.0,10,"Xiaomi","10000mAh",1000));

        try {
            System.out.println("Iniciando Servidor CORBA...");

            // 2. Inicializa o ORB
            ORB orb = ORB.init(args, null);

            // 3. Ativa o POA (Portable Object Adapter)
            POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
            rootpoa.the_POAManager().activate();

            // 4. Instancia o Servidor e exporta a referência
            ServidorCatalogoImpl servicoImpl = new ServidorCatalogoImpl(catalogo_Geral);
            org.omg.CORBA.Object ref = rootpoa.servant_to_reference(servicoImpl);
            CatalogoApp.ServicoCatalogo href = CatalogoApp.ServicoCatalogoHelper.narrow(ref);

            // 5. Registra o serviço no Naming Service para o cliente C++ encontrar
            org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
            NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
            
            NameComponent path[] = ncRef.to_name("CatalogoRemoto");
            ncRef.rebind(path, href);

            System.out.println("Servidor pronto!");
            
            // 6. O ORB bloqueia a thread e fica escutando a rede
            orb.run(); 

        } catch (Exception e) {
            System.err.println("Erro no servidor: " + e.getMessage());
            e.printStackTrace();
        }
    }
}