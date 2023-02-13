FROM 'pandoc/extra'
COPY entrypoint.sh /entrypoint.sh
COPY README.md /README.md
ENTRYPOINT ["/entrypoint.sh"]