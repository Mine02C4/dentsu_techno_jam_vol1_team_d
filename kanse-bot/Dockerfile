FROM centos

RUN cp -pn  /usr/share/zoneinfo/Japan /etc/localtime

RUN yum -y update
RUN yum -y groupinstall "Development Tools"

RUN yum -y install ruby-devel gem
RUN gem install td

RUN yum -y install python-devel libffi-devel openssl-devel
RUN curl -kL https://raw.github.com/pypa/pip/master/contrib/get-pip.py | python
RUN pip install pyopenssl ndg-httpsclient pyasn1 urllib3
RUN pip install Twython
RUN pip install td-client pytz
