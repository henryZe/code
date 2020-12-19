# Django Buildup

## 1 Build-up 'Hello-World' Command

### 1.1 Create Project

* django-admin startproject mysite
> Create 'mysite' project

### 1.2 Modify Project

* python manage.py startapp hello_app
> Create 'hello_app' application

* modify views.py of hello_app for adding new view function named 'hello'
> Add 'hello' function in views.py

* import hello_app in urls.py of mysite, and add new path in urls list
> link specific path to 'hello' function

### 1.3 Run Web Server

* python manage.py runserver
> run web server

## 2 MTV Development Mode

* Model: data structure
* Template: display strategy
* View: deal user requests

urls.py: specify path
models.py: specific model
views.py: response views

