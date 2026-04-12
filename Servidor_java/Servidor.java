package Servidor_java;

import java.net.*;
import java.io.*;
import java.nio.*;

import java.util.Properties;

import Servidor_java.Modelos.Celular;

import Servidor_java.Servicos.CatalogoCelular;
import Servidor_java.Servicos.GestorVendas;

import Servidor_java.Stream.PojoInputstream;
import Servidor_java.Stream.PojoOutputStream;

import Servidor_java.Utils.FileOutputStream_catalogo;

public class Servidor {

    public static void main(String args[]){
        
        CatalogoCelular catalogo_celular = new CatalogoCelular();
        FileOutputStream_catalogo.carregarCatalogo(catalogo_celular);

        if (catalogo_celular.getTodos().isEmpty()) {
            catalogo_celular.adicionarCelular(new Celular(1,"IPhone 15","Apple celular",5000.0,5,"Apple","15 Pro"));
            catalogo_celular.adicionarCelular(new Celular(2,"Poco 11","Celular xiaomi poco 11",5000.0,5,"Xiaomi","poco 11"));
        }
        
        ServerSocket server = null;


        try {
            
            Properties prop = new Properties();
            
            prop.load(new FileInputStream("Servidor_java/config.properties"));
            String host = prop.getProperty("server.host");
            int porta = Integer.parseInt(prop.getProperty("server.porta"));
            System.out.println("Servidor iniciado em " + host + " : " + porta);

            
            server = new ServerSocket(porta);
            PojoOutputStream saida;
            

            for(;;){
                
                try {

                    System.out.println("Aguardando conexões.");            
                    Socket cliente = server.accept();
                    System.out.println("Cliente conectado: " + server.getInetAddress());
                    
                    
                    //iniciando serialização
                    InputStream entrada = cliente.getInputStream();
                    PojoInputstream pojo_stream;
                    
                    byte[] buffer = new byte[4];
                    entrada.read(buffer);
                
                    int tamanho_pacote = ByteBuffer.wrap(buffer).order(ByteOrder.BIG_ENDIAN).getInt();
                    System.out.println("Tamanho do pacote recebido: " + tamanho_pacote + " bytes");
                
                    byte[] data_buffer = new byte[tamanho_pacote];
                    entrada.read(data_buffer);
                    
                    
                    pojo_stream = new PojoInputstream(new ByteArrayInputStream(data_buffer));
                    int quantidade_produtos = pojo_stream.lerInt_LE();
                    
                    System.out.println("Recebido " + quantidade_produtos + " Produtos");
                    
                    for(int i=0; i < quantidade_produtos; i++){
                        Celular c = pojo_stream.lerCelular_LE();
                        catalogo_celular.adicionarCelular(c);

                        //Teste de implementação por saida padrao
                        System.out.println("Item " + (i+1) + " adicionado  no catalogo: " + c.getNome() + " - " + c.getDescricao() + " - " + c.getPreco() + " - " + c.getMarca() + " - " + c.getModelo());
                    }
                    
                
                    var listaCelulares = catalogo_celular.getTodos();
                    Celular[] arrayCelulares = listaCelulares.toArray(new Celular[0]);
                        
                    saida = new PojoOutputStream(arrayCelulares,arrayCelulares.length, cliente.getOutputStream());
                    saida.enviarDados();
                    saida.close();
                    

                    FileOutputStream_catalogo.salvarCatalogo(catalogo_celular);
                    FileOutputStream_catalogo.salvarCatalogoCsv(catalogo_celular);

                    
                    System.out.println("Conexão encerrada pelo cliente.");            
                    cliente.close();

                } catch (IOException e) {
                    System.out.println("Erro ao processar cliente: " + e.getMessage());
                    e.printStackTrace();
                }
            }

        } catch (FileNotFoundException e) {
            System.out.println("Erro: arquivo .properties nao encontrado");

        }catch (IOException e) {
           System.out.println("erro de IO no .properties");
        }catch (NumberFormatException e) {
            System.out.println("erro de formatação do .properties");
        }finally {
            System.out.println("Servidor encerrado.");
        }




    }
}

