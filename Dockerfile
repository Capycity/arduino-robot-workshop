FROM 'pandoc/extra:3.0-alpine'
COPY entrypoint.sh /entrypoint.sh
COPY README.md /README.md
ENTRYPOINT ["/entrypoint.sh"]