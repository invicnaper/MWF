/* 
 *  ______            _______  _______  _______  _______ 
 * (  ___ \ |\     /|(  ____ \(  ___  )(  ____ )(  ____ )
 * | (   ) )| )   ( || (    \/| (   ) || (    )|| (    )|
 * | (__/ / | |   | || (_____ | (___) || (____)|| (____)|
 * |  __ (  | |   | |(_____  )|  ___  ||  _____)|  _____)
 * | (  \ \ | |   | |      ) || (   ) || (      | (      
 * | )___) )| (___) |/\____) || )   ( || )      | )      
 * |/ \___/ (_______)\_______)|/     \||/       |/ 
 * [+] Busapp by Hamza 
 * [+] www.naper.eu
 * [+] designed to be elegant ^^
 */

/* global variables   */

var radio = document.getElementById("");
var len = document.f.optionsRadios.lenght;

/* end global variables  */

function draw_informations(){
    var date = new Date();
    var hours = date.getHours();
    var days = date.getDay(); 
    
    var month = date.getMonth();
    var year = date.getFullYear();
    var minutes = date.getMinutes();
    var ampm = hours >= 12 ? 'pm' : 'am';
    hours = hours % 12;
    hours = hours ? hours : 12; // the hour '0' should be '12'
    minutes = minutes < 10 ? '0'+minutes : minutes;
    var strTime = date + ' ' + hours + ':' + minutes + ' ' + ampm;
    document.write('<p id="full_time"><h6>Full Time : <b>'+ days +'/'+ month  + '/' + year + ' ' + hours + ':' + minutes +'</b></h6></p>');
    document.write('<p id="Date"><h6>Date : <b>'+ days +'/'+ month  + '/' + year +'</b></h6></p>');
    document.write('<p id="server"><h6>Server  : <b>On</b></h6></p>');
    document.write('<p id="time"><h6>Time  : <b>'+ Date.getTime() +'</b></h6></p>');
}
function update_informations(){

}

function print_draw_radio1(radio1){
   /* check radio select */
   if (radio1.checked == true){
       $('#r2').wrapInner('<fieldset id="fs2" disabled>');
   }else {
   }
}
function print_draw_radio2(radio2){
   /* check radio select */
   if (radio2.checked == true){
       $('#inp').html();
       $('#inp').html('<div id="r2"><input class="form-control" placeholder="Par exemple: 1-5,8,9"></div>');
       
   }else {
       
   }
}
function print_draw_progresbar(position){
    /* printing progressbar  */
        document.write("<div>");
        document.write("<p>");
        document.write("<strong>Imprimer</strong>");
        document.write('<span class="pull-right text-muted">0% Complete</span>');
        document.write("</p>");
        document.write('<div class="progress progress-striped active">');
        document.write('<div class="progress-bar progress-bar-info" role="progressbar" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100" style="width: '+ position + '%">');
        document.write('<span class="sr-only">0% Complete</span>');
        document.write('</div>');
        document.write('</div>');
        document.write('</div>');
        position = position + 10;
}
function print_draw_progresbar_position(){
    /* testing the magic of jquery :D   */
}

/*
 *=====================================  
 *          Add account check
 *=====================================
 */
function addacc_draw_button(champ){
    /* testing the magic of jquery :D   */
    var button = document.getElementById("btnadd");
    var div_email = document.getElementById("emr");
    var my_champ = document.getElementById("email");
    if (champ.value === ""){
        button.className = "btn btn-primary btn-lg btn-block disabled";
        div_email.className = "form-group has-error";
        my_champ.placeholder = "E-mail is empty";
    }else{
        div_email.className = "form-group has-success";
        button.className = "btn btn-primary btn-lg btn-block ";
    }
}
function check_firstname(champ){
    var my_div = document.getElementById("fnr");
     var my_champ = document.getElementById("fname");
    if(champ.value === ""){
        my_div.className = "form-group has-error";
        my_champ.placeholder = "First Name is empty";
    }else{
        my_div.className = "form-group has-success";
    }
}
function check_lastname(champ){
    var my_div = document.getElementById("lnr");
     var my_champ = document.getElementById("lname");
    if(champ.value === ""){
        my_div.className = "form-group has-error";
        my_champ.placeholder = "Last Name is empty";
    }else{
        my_div.className = "form-group has-success";
    }
}
function check_password(champ){
    var my_div = document.getElementById("par");
    var my_champ = document.getElementById("pass");
    if(champ.value === ""){
          my_div.className = "form-group has-error";
          my_champ.placeholder = "Password is empty";
    }else{
          my_div.className = "form-group has-success";
    }
}

/*
 *=====================================  
 *         End Add account check
 *=====================================
 */
/*
 *=====================================  
 *         Add notaire check
 *=====================================
 */
function addacc_not_button(champ){
    /* testing the magic of jquery :D   */
    var button = document.getElementById("btnadd");
    var div_email = document.getElementById("emr");
    var my_champ = document.getElementById("email");
    if (champ.value === ""){
        button.className = "btn btn-primary btn-lg btn-block disabled";
        div_email.className = "form-group has-error";
        my_champ.placeholder = "Nom du notaire est vide";
    }else{
        div_email.className = "form-group has-success";
        button.className = "btn btn-primary btn-lg btn-block ";
    }
}
function check_tel(champ){
    var my_div = document.getElementById("fnr");
     var my_champ = document.getElementById("fname");
    if(champ.value === ""){
        my_div.className = "form-group has-error";
        my_champ.placeholder = "Tel est vide";
    }else{
        my_div.className = "form-group has-success";
    }
}
function check_adresse(champ){
    var my_div = document.getElementById("lnr");
     var my_champ = document.getElementById("lname");
    if(champ.value === ""){
        my_div.className = "form-group has-error";
        my_champ.placeholder = "Adresse du notaire est vide";
    }else{
        my_div.className = "form-group has-success";
    }
}
function check_responsable(champ){
    var my_div = document.getElementById("par");
    var my_champ = document.getElementById("pass");
    if(champ.value === ""){
          my_div.className = "form-group has-error";
          my_champ.placeholder = "Responsable est vide";
    }else{
          my_div.className = "form-group has-success";
    }
}
/*
 *=====================================  
 *         End notaire check
 *=====================================
 */

/*
 *=====================================  
 *         Profil functions
 *=====================================
 */

function draw_timeline(){
    
}
function update_progressbar(){
    
}
function show_message_area(btn){
    var nb_clique = nb_clique + 1;
    var div_message = document.getElementById("smsg");
    //div_message.style = "visibility: visible";
    document.getElementById('smsg').style.visibility = 'visible';
}
function active_sendbtn(champ){
    /*  to enable the send btn  */
    
    var button = document.getElementById("sendbtn");
    if(champ.value === ""){
        button.className = "btn btn-success disabled";
    }else {
        button.className = "btn btn-success";
    }
}

/*
 *=====================================  
 *         End Profil functions
 *=====================================
 */

/*
 *=====================================  
 *         Saisie Projet functions
 *=====================================
 */

    function show_errors(){
        if (nb_erros>0){
            
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_name_proj(champ, nb_erros){
        /*  check name project value  */
        var div_nproj = document.getElementById("d_nproj");
        var btn = document.getElementById("btn_cancel");
        btn.className = "btn btn-danger";
        if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ Nom du projet est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_situation(champ, nb_erros){
         /*  check situation value  */
       var div_nproj = document.getElementById("d_sit");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ Situation est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_consistance(champ, nb_erros){
        /*  check consitance value  */
       var div_nproj = document.getElementById("d_con");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ Consistance est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_superficie(champ, nb_erros){
        /*  check superficie value  */
       var div_nproj = document.getElementById("d_super");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ superficie est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_dateauto(champ, nb_erros){
         /*  check date autorisation value  */
       var div_nproj = document.getElementById("d_dauto");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ date autorisation est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_numero(champ, nb_erros){
         /*  check numero value  */
       var div_nproj = document.getElementById("d_num");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ numéro est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_dater(champ, nb_erros){
         /*  check date de reception value  */
       var div_nproj = document.getElementById("d_drec");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ date de réception est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_cout(champ, nb_erros){
        /*  check date de reception value  */
       var div_nproj = document.getElementById("d_cout");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ cout est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
        }
    }
    function check_nbjmax(champ, nb_erros){
         /*  check nombre de jour max value  */
       var div_nproj = document.getElementById("d_nbjmax");
       if(champ.value === ""){
            div_nproj.className = "form-group has-error";
            $('#d_error').html();
            $('#d_error').html('champ nombre de jour max est vide. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-danger";
            nb_erros ++;
        }else {
            div_nproj.className = "form-group has-success"; 
               nb_erros --;
        }
        if (nb_erros>0){
        }else {
            $('#d_error').html('Aucune. <a href="#" class="alert-link">retour</a>.');
            document.getElementById("d_error").className = "alert alert-success";
            document.getElementById("btn_send").className = "btn btn-success";
        }
    }
    function show_date_nbmax(champ){
        /*  function that allows to show date of reservation */
        var date = new Date();
        var hours = date.getHours();
        var days = date.getDay();

        var month = date.getMonth();
        var year = date.getFullYear();
        var minutes = date.getMinutes();

        var today = days +'/'+ month  + '/' + year ;
        var my_date = champ.value;
        var tmp_date = days + my_date;

    }
    function post_insert(btn){
        /*  show a gif image   */
        $('#btn_send').after('&nbsp;<img id ="iload" src ="images/ajax-loader_gris.gif" height="20" width="30" />');
        $('#btn_send').remove();
        /*  POST */
        var xhr = new XMLHttpRequest();

        xhr.open('POST', 'insert.php');

        xhr.upload.onprogress = function(e) {

        };

        xhr.onload = function() {
            //window.location.href = "insert.php"
            $('#d-body').html();
            $('#d-body').html('<div class="alert alert-success">Projet ajouté. <a href="#" class="alert-link">retour</a>.</div>');
        };
        var form = new FormData;
        form.append('form_type','sproj');
        form.append('namep',document.getElementById("nproj").value);
        form.append('socitp',document.getElementById("socitp").value);
        form.append('situationp',document.getElementById("situationp").value);
        form.append('titref', document.getElementsByName("titref").value);/* ajouter titref */
        form.append('superficie',document.getElementById("superficie").value);
        form.append('consistance',document.getElementById("consistance").value);
        form.append('nature',document.getElementById("nature").value);
        form.append('datedautop',document.getElementById("datedautop").value);
        form.append('numerod',document.getElementById("numerod").value);
        form.append('datedereception',document.getElementById("datedereception").value);
        form.append('coutrev',document.getElementById("coutrev").value);
        form.append('nbrjourreservation',document.getElementById("nbrjourreservation").value);
        xhr.send(form);
    }
    function show_uploaded_images(btn){
        /*  this function  will show all picture uploaded for a project , and do a simple maths operation ;)  */

        $('#addp').after('<input type="file"  id="file" name="file" />'); /*  show the file btn  */
        $('#addp').after('<script>var nb_image = 0;upload_file(nb_image);</script>');

    }
    function upload_file(nb_image){
        /*  the code that allows as to upload a file  */
        var fileInput = document.querySelector('#file');
        var allowedTypes = ['png', 'jpg', 'jpeg', 'gif'],
            fileInput = document.querySelector('#file'),
            prev = document.querySelector('#prev');
        fileInput.onchange = function() {
            $('#p_show').html();
            $('#p_show').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: 1%"><span class="sr-only">20% Complete</span></div></div>');
            progress = document.getElementById('#v_progress');
            var xhr = new XMLHttpRequest();

            xhr.open('POST', 'upload.php');

            xhr.upload.onprogress = function(e) {
                progress.style = $('#p_show').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: '+ e.loaded +'%"><span class="sr-only">20% Complete</span></div></div>');
            };

            xhr.onload = function() {
                nb_image ++;
                $('#p_show').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: 100%"><span class="sr-only">20% Complete</span></div></div>');
                /*  show picture */
                var img1 = document.getElementById("img1");
                var modal_img = document.getElementById("m_img");
                switch(nb_image){
                    case 1:
                        $('#p_show').empty();
                        $('#all_img').html();
                        modal_img.src = "uploads/" + fileInput.files[0].name;
                        $('#all_img').html('<a href="#" data-toggle="modal" data-target="#s_img"><img id ="img1" src="uploads/'+ fileInput.files[0].name +'" height="150" width="220" /></a>');
                        break;
                    case 2:
                        $('#p_show').empty();
                        img1.height = "75";
                        img1.width  = "110";
                        $('#img1').after('&nbsp;&nbsp;<a href="#"><img id="img2" src="uploads/'+ fileInput.files[0].name +'" height="75" width="110" /></a>');
                        break;
                    default:
                        break;
                }
            };

            var form = new FormData();
            form.append('file', fileInput.files[0]);

            xhr.send(form);


        };

    }
    function draw_tab_product(){
        /* willd raw tab of product */
        /*
        $('#tab_list').text({
            serviceUrl: 'result.php',
            dataType: 'json'
        });
        */
        alert('ok');
        $('#tab_list').html('<p>xd</p>');

    }

/*
 *=====================================  
 *         End Saisie Projet functions
 *=====================================
 */

/*
 *=====================================
 *         Saisie Produits functions
 *=====================================
 */
function check_numero(champ, nb_errors){

}
function check_type(champ, nb_errors){

}
function check_etage(champ, nb_errors){

}
function draw_prod_pagination(max_draw, nb_rows){
    /* drawing pagination  */
    /* we will caclul the nb page that we will show with a simple operation. MaxRows and and totalrows prod  */
    var nb_page = nb_rows / max_draw;
    var total_page = 0;var i ;
    if(nb_page < 1){
        var total_page = 1;
        document.write('<ul  class="pagination"><li class="paginate_button previous disabled" aria-controls="dataTables-example" tabindex="0" id="dataTables-example_previous"><a href="#">Previous</a></li>'
            + '<li class="paginate_button active" aria-controls="dataTables-example" tabindex="0"><a href="#">0</a></li>'
            + '<li class="paginate_button next disabled" aria-controls="dataTables-example" tabindex="0" id="dataTables-example_next"><a href="#">Next</a></li></ul>');
    }
    else {
        document.write('<ul  class="pagination"><li class="paginate_button previous disabled" aria-controls="dataTables-example" tabindex="0" id="dataTables-example_previous"><a href="#">Previous</a></li>');
        for(i = 0; i<=nb_page ;i++){
            total_page ++;
            draw_prod_number(i);
        }
        document.write('<li class="paginate_button next" aria-controls="dataTables-example" tabindex="0" id="dataTables-example_next"><a href="#">Next</a></li></ul>');
    }
}
function draw_prod_number(number){
    if(number == document.getElementById("p_num").innerText){
        document.write('<li class="paginate_button active" aria-controls="dataTables-example" tabindex="0"><a href="?act=lproj&pageNum_alc_menu='+ number +'">'+ number +'</a></li>');
    }
    else {
        document.write('<li class="paginate_button" aria-controls="dataTables-example" tabindex="0"><a href="?act=lproj&pageNum_alc_menu='+ number +'">'+ number +'</a></li>');
    }
}
/*
 *=====================================
 *        End Saisie produits functions
 *=====================================
 */

/*
 *=====================================
 *         Send message
 *=====================================
 */
function update_date(){
    /*  date between the message and time , return this date  */

}

function show_upload_image() {
    $('#s_file').before('<div id="up_btn"><input type="file"  id="file" name="file" /></div>'); /*  show the file btn  */
    $('#s_file').before('<script>upload_image();</script>');
}
function show_upload_file(){
    $('#s_file').before('<div id="up_btn"><input type="file"  id="file_up" name="file_up" /></div>'); /*  show the file btn  */
    $('#s_file').before('<script>upload_file();</script>');
}
function upload_image(){
    /*  the code that allows as to upload a file  */
    var fileInput = document.querySelector('#file');
    var allowedTypes = ['png', 'jpg', 'jpeg', 'gif'],
        fileInput = document.querySelector('#file'),
        prev = document.querySelector('#prev');
    fileInput.onchange = function() {
        $('#s_file').html();
        $('#s_file').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: 1%"><span class="sr-only">20% Complete</span></div></div>');
        progress = document.getElementById('#v_progress');
        var xhr = new XMLHttpRequest();

        xhr.open('POST', 'upload.php');

        xhr.upload.onprogress = function(e) {
            progress.style = $('#s_file').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: '+ e.loaded +'%"><span class="sr-only">20% Complete</span></div></div>');
        };

        xhr.onload = function() {
            //$('s_file').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: 100%"><span class="sr-only">20% Complete</span></div></div>');
            $('#d_n').empty();
            $('#s_file').html('<img id ="up_img" src="uploads/'+ fileInput.files[0].name + '" height="40" width="40" />');
            $('#up_btn').remove();

        };

        var form = new FormData();
        form.append('file', fileInput.files[0]);

        xhr.send(form);


    };
}
function upload_file(){
    /*  the code that allows as to upload a file  */
    var fileInput = document.querySelector('#file_up');
    var allowedTypes = ['png', 'jpg', 'jpeg', 'gif', 'pdf', 'doc'],
        fileInput = document.querySelector('#file_up'),
        prev = document.querySelector('#prev');
    fileInput.onchange = function() {
        $('#s_file').html();
        $('#s_file').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: 1%"><span class="sr-only">20% Complete</span></div></div>');
        progress = document.getElementById('#v_progress');
        var xhr = new XMLHttpRequest();

        xhr.open('POST', 'upload.php');

        xhr.upload.onprogress = function(e) {
            progress.style = $('#s_file').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: '+ e.loaded +'%"><span class="sr-only">20% Complete</span></div></div>');
        };

        xhr.onload = function() {
            //$('s_file').html('<div  id="progres" class="progress progress-striped active"><div class="progress-bar progress-bar-info" id="v_progress" role="progressbar" aria-valuenow="20" aria-valuemin="0" aria-valuemax="100" style="width: 100%"><span class="sr-only">20% Complete</span></div></div>');
            $('#d_f').html('<img id="label_src" src="'+ fileInput.files[0].name  +'" height="1" width="0" />');
            $('#s_file').html('<div id="up_f"><img id="up_img" src="" height="0" width="0" /><img src="images/attachment_blue.png" height="20" width="20" /> <b id="file_l">'+ fileInput.files[0].name  +'</b></div>');
            $('#up_btn').remove();
        };

        var form = new FormData();
        form.append('file_up', fileInput.files[0]);

        xhr.send(form);
    };
}
function draw_delete(){
    /*  this function allows us to draw checkboxe so as to delete messages  */
}

/*
 *=====================================
 *         End Send message
 *=====================================
 */

/*
 *=====================================
 *         Timeline
 *=====================================
 */
function draw_statut_option(champ){
    /*  we will draw option of timeline   */
    $('#opt').html('<div class="row show-grid">'
        + '<div class="col-md-4">.col-md-4</div>'
        + '<div class="col-md-4 col-md-offset-4">.col-md-4 .col-md-offset-4</div>'
        + '</div>');
}
function draw_preview(){
    /*  draw preview url   */
}
function draw_like(){
    /* function that allows us to draw lik and unlike and submit them */
    var like = $('#like').text();

        /*  send a XHR  */
        var xhr = new XMLHttpRequest();

        xhr.open('POST', 'insert.php');

        xhr.upload.onprogress = function(e) {

        };

        xhr.onload = function() {
            $('#like').text('UnLike');
        };

        var form = new FormData();
        form.append('form_type', 'like');
        form.append('id_user', document.getElementById("id_user").src);
        form.append('id_notif', document.getElementById("id_notif").src);
        form.append('id_post', document.getElementById("id_post").src);

        xhr.send(form);

}
function draw_unlike(){
    /* function that allows us to draw lik and unlike and submit them */
    var like = $('#unlike').text();
    /*  send a XHR  */
    var xhr = new XMLHttpRequest();

    xhr.open('POST', 'insert.php');

    xhr.upload.onprogress = function(e) {

    };

    xhr.onload = function() {
        $('#unlike').text('Like');
    };

    var form = new FormData();
    form.append('form_type', 'unlike');
    form.append('id_like', document.getElementById("_id_like").src);


    xhr.send(form);

}
/*
 *=====================================
 *         End Timeline
 *=====================================
 */

/*
 *=====================================
 *         Installation
 *=====================================
 */
function check_host(champ){
    var my_div = document.getElementById("d_host");
    if(!champ.value){
        my_div.className = "form-group has-error";
    }else{
        my_div.className = "form-group has-success";
    }
}
function check_user(champ){
    var my_div = document.getElementById("d_user");
    if(!champ.value){
        my_div.className = "form-group has-error";
    }else{
        my_div.className = "form-group has-success";
    }
}
function check_db(champ){
    var my_div = document.getElementById("d_db");
    if(!champ.value){
        my_div.className = "form-group has-error";
    }else{
        my_div.className = "form-group has-success";
    }
}
function check_passe(champ){
    var my_div = document.getElementById("d_passe");
    if(!champ.value){
        my_div.className = "form-group has-error";
    }else{
        my_div.className = "form-group has-success";
    }
}

/*
 *=====================================
 *         END Installation
 *=====================================
 */

