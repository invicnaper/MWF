/*
 * Created by Hamza on 24/07/14.
 *[+]description : Jshow is a function that allows sending forms and showing results with out loading pages. It uses XHR to send request . just creat a form
 * and enjoy the result :) .
 *[+]author: hamza bourrahim
 *[+]github: www.github.com/invicnaper
 */

function load_jshow(page, name_form, result, btn_id){
    /*  we will detect all inputs or others from the id form  */
    $('#'+ btn_id).after('&nbsp;<img id ="iload" src ="ajax-loader_gris.gif" height="20" width="30" />');
    $('#'+ btn_id).remove();
    /*  POST */
    var xhr = new XMLHttpRequest();var i;

    xhr.open('POST', page);

    xhr.upload.onprogress = function(e) {
        /*  progressing : add what you want :)  */
    };

    xhr.onload = function() {
        /*  page loaded then show result */
        draw_result(result);
    };
    var form = new FormData; /* creat a new form */

    var elements = document.forms[name_form].elements;/* getting all elements of the form we have */

    for (i=0; i<elements.length; i++){
        /* adding all elements to the form we've created */
        form.append(elements[i].name, elements[i].value);
    }
    xhr.send(form);/*  sending the form we've created */

}
function draw_result(selector){
    $('#'+ selector).html('Form submitted :D');
}
function draw_error(selector){
    $('#'+ selector).html('error while submitting the form');
}