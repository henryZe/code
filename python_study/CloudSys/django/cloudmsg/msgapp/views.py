import os
from django.shortcuts import render
from datetime import datetime
from django.http import HttpResponse, JsonResponse, FileResponse, StreamingHttpResponse, HttpResponseNotFound
from django.views.decorators.http import require_http_methods
from django.template import Context, Template
from django.template.loader import get_template

# filter of http methods
@require_http_methods(["GET", "POST"])
# Create your views here.
def msgproc(request):
    datalist = []

    if request.method == 'POST':
        userA = request.POST.get('userA', None)
        userB = request.POST.get('userB', None)
        msg = request.POST.get('msg', None)
        time = datetime.now()
        with open('msgdata.txt', 'a+') as f:
            f.write("{}--{}--{}--{}--\n".format(userB, userA, msg, time.strftime("%Y-%m-%d %H:%M:%S")))

    if request.method == 'GET':
        userC = request.GET.get('userC', None)
        if userC != None:
            with open('msgdata.txt', 'r') as f:
                cnt = 0
                for line in f:
                    linedata = line.split('--')
                    if linedata[0] == userC:
                        cnt += 1
                        d = {'userA': linedata[1], 'msg': linedata[2], 'time': linedata[3]}
                        datalist.append(d)
                    if cnt >= 10:
                        break

    # return render(request, "msg_single_web.html", {'data': datalist})

    try:
        tpl = get_template("msg_single_web.html")
    except:
        return HttpResponseNotFound("<h1>self-defined 404</h1>")
    # render(context, request)
    # mixes template & context(dict) as html
    html = tpl.render({"data": datalist}, request)
    return HttpResponse(html)

def file_iterator(file_name, chunk_size = 512):
    with open(file_name) as f:
        while True:
            c = f.read(chunk_size)
            if c:
                yield c
            else:
                break

def homeproc(request):
    homeproc_type = 5

    if homeproc_type == 1:
        return HttpResponse("<h1>Here is home page, and please visit <a href='./msggate'>here</a> for details.</h1>")

    if homeproc_type == 2:
        response = HttpResponse()
        response.write("<h1>Here is home page, and please visit <a href='./msggate'>here</a> for details.</h1>")
        response.write("<h1>Here is the second line.</h1>")
        return response

    if homeproc_type == 3:
        response = JsonResponse({'key': 'value1'})
        return response

    # big file download
    cwd = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    if homeproc_type == 4:
        # MIME standard file
        response = FileResponse(open(cwd + '/msgapp/templates/pylogo.png', 'rb'))
        # file type
        response['Contest-Type'] = 'application/octet-stream'
        # default name of downloaded file
        response['Contest-Disposition'] = 'attachment;filename=“pylogo.png”'
        return response

    if homeproc_type == 5:
        fname = cwd + '/msgdata.txt'
        response = StreamingHttpResponse(file_iterator(fname))
        return response

def pgproc(request):
    tpl = Template("<h1>This program's name is {{ name }}.</h1>")
    ctx = Context({'name': 'Test Platform'})
    return HttpResponse(tpl.render(ctx))
