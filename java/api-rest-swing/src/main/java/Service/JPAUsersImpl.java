package Service;

import model.User;

import java.util.ArrayList;
import java.util.List;


public class JPAUsersImpl implements JPAUsers {
    private List<User> users = new ArrayList<User>();        
    public static User user;

    @Override
    public String create(String body) {

        String[] data = body.split(",");

        user = new User(0, data[0], data[1], data[2]);
        String response = "Se ha creado el usuario con exito y sus datos son:\n" + "Id:" + user.getId() + ", " + " Nombres: " + user.getNames() + ", " +
                "Email: " + user.getEmail() + ", " + "Teléfono: " + user.getPhone();
        //int id = users.size()+ 1;
        //user.setId(id);//sino se le asigna el id, el id siempre será el mismo
        //user.setId(User.getId()+1);//incrementamos el id automaticamente cada vez que se cree un nuevo usuario
        users.add(user);//adicionamos el objeto
        return response;
        // System.out.println(response);
    }


    @Override
    public List<User> readAll() {
        users.add(new User(1, "Juan Pérez", "juan.perez@email.com", "123456789"));
        users.add(new User(2, "Ana Gómez", "ana.gomez@email.com", "987654321"));
        users.add(new User(3, "Carlos López", "carlos.lopez@email.com", "456789123"));
        users.add(new User(4, "Maria Rodríguez", "maria.rodriguez@email.com", "321654987"));
        return users;        
    }

    //prod = new Producto(listaProductos.get(i).getCodigo(), nombre, descrip, pCompra, pVenta, cantidad);
    //listaProductos.set(i, prod); // se agrega en la posicion del codigo encontrado, el nuevo objeto con sus parametros
    @Override
    public String updateById(String body, int id) throws IndexOutOfBoundsException {
        //int indice = users.indexOf(id);
        //if (indice != -1) {    //si el indice es diferente de -1, es decir, si existe el usuario

        for (User usuario : users) {
            if (usuario.getId() == id) {
                String[] data = body.split(",");
                user.setNames(data[0]);
                user.setEmail(data[1]);
                user.setPhone(data[2]);
                users.set(id, user);
                //user.setId(id);//reconfirmamos  el id
                break;
            }
        }//end for
        String Response = "Se ha actualizado el usuario con éxito y sus datos son:\n" + "Id:" + user.getId() + ", " + " Nombres: " + user.getNames() + ", " +
                "Email: " + user.getEmail() + ", " + "Teléfono: " + user.getPhone();
        return Response;
        // System.out.println("Se ha actualizado el usuario con éxito y sus datos son:\n" + "Id:" + user.getId() + ", " + " Nombres: " + user.getNames() + ", " +
        //         "Email: " + user.getEmail() + ", " + "Teléfono: " + user.getPhone());
        //} else {
        //   System.out.println("No se ha encontrado el usuario con el id: " + id);
        // }
    }


    @Override
    public String deleteById(int id) throws IndexOutOfBoundsException {
        //for (User usuario : users) {
        users.removeIf(p -> p.getId() == id);
        //if (usuario.getId() == id) {
        //encontrado = true;
        //users.remove(usuario);

        // break;
        //}
        //}//end for
        /*if(encontrado ==false)

    {
        System.out.println("No se ha encontrado el usuario con el id: " + id);
    };*/
    String Response = "Se ha eliminado el usuario con Id:" + id;
    return Response;
        // printUsers(users);

    }

    @Override
    public String findAll() {
        return "";
    }

    @Override
    public String findById(int id) {
        users.add(new User(1, "Juan Pérez", "juan.perez@email.com", "123456789"));
        users.add(new User(2, "Ana Gómez", "ana.gomez@email.com", "987654321"));
        users.add(new User(3, "Carlos López", "carlos.lopez@email.com", "456789123"));
        users.add(new User(4, "Maria Rodríguez", "maria.rodriguez@email.com", "321654987"));
        String Response = "";
        for (User usuario : users) {
            if (usuario.getId() == id) {
                Response = "Se ha encontrado el usuario:" + usuario.getNames();  
                break;              
            }
            else{
                 Response = "No se ha encontrado un usuario con el Id: " + id; 
            }
        }
        return Response;
    }


}
