package Service;

import model.User;

import java.util.List;

public interface JPAUsers {
    /*Interfaz que contendrá los métodos abtractos(CRUD)
    *que se implementarán en la clase JPAUsersImpl
     */

    public String create(String body);
    public List<User>  readAll();
    public String updateById(String body, int id);
    public String deleteById(int id);
    public String findAll();
    public String findById(int id);

}

